// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Gameplay/Player/ShifterCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Framework/ShifterPlayerController.h"
#include "Framework/ShiftersGameMode.h"
#include "Framework/Input/CharacterShiftInputAction.h"
#include "Gameplay/Abilities/Ability.h"
#include "Gameplay/Obstacles/Obstacle.h"
#include "Gameplay/World/ShifterSpawner.h"
#include "Kismet/GameplayStatics.h"


class UEnhancedInputLocalPlayerSubsystem;
// Sets default values
AShifterCharacter::AShifterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	ObstacleCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	// SetRootComponent(ObstacleCollisionBox);
	ObstacleCollisionBox->SetupAttachment(GetRootComponent());
	ObstacleCollisionBox->SetGenerateOverlapEvents(true);
	ShapeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShapeMesh"));
	ShapeMesh->SetupAttachment(GetRootComponent());
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	ViewCamera->SetupAttachment(GetRootComponent());
	LaneIndex = 0;
	CurrentScore = 0.f;
	bCanMove = true;
}

// Called when the game starts or when spawned
void AShifterCharacter::BeginPlay()
{
	Super::BeginPlay();
	TargetLocation = GetActorLocation();
	ObstacleCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShifterCharacter::OnCollision);
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ShapeMesh->SetStaticMesh(*ShiftersGameMode->ShapeMeshTable.Find(ShiftersGameMode->ShapeLoadout[0]));
		for(auto& Shape : ShiftersGameMode->ShapeLoadout)
		{
			if(UAbility** Ability = ShiftersGameMode->ShapeAbilityTable.Find(Shape))
			{
				(*Ability)->InitializeAbility(false);
			}
		}
	}
}

void AShifterCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if(APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* InputSystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(InputMappingContext, 1);
		}
	}
}

void AShifterCharacter::HandleLaneMovement(const FInputActionInstance& Action)
{
	if(bCanMove)
	{
		float InputData = Action.GetValue().Get<float>();
		if(InputData < 0.f)
		{
			StepLeft();
		
		}else if(InputData > 0.f)
		{
			StepRight();
		}
	}
}

void AShifterCharacter::HandleSwapCharacter(const FInputActionInstance& Action)
{
	if(const UCharacterShiftInputAction* ShiftInputAction = Cast<UCharacterShiftInputAction>(Action.GetSourceAction()))
	{
		if(Action.GetValue().Get<bool>())
		{
			if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
			{
				ShiftersGameMode->ShiftPlayer(this, ShiftersGameMode->ShapeLoadout[ShiftInputAction->ShapeIndex]);
			}
		}	
	}
}

void AShifterCharacter::HandleUseAbility(const FInputActionInstance& Action)
{
	if(Action.GetValue().Get<bool>())
	{
		if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
		{
			if(UAbility** Ability = ShiftersGameMode->ShapeAbilityTable.Find(CurrentShapeType))
			{
				(*Ability)->ActivateAbility(this);
			}
		}
	}
}

void AShifterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LaneChangeInputLeft, ETriggerEvent::Triggered, this, &AShifterCharacter::HandleLaneMovement);
		EnhancedInputComponent->BindAction(LaneChangeInputRight, ETriggerEvent::Triggered, this, &AShifterCharacter::HandleLaneMovement);
		EnhancedInputComponent->BindAction(SwapCharacter1, ETriggerEvent::Triggered, this, &AShifterCharacter::HandleSwapCharacter);
		EnhancedInputComponent->BindAction(SwapCharacter2, ETriggerEvent::Triggered, this, &AShifterCharacter::HandleSwapCharacter);
		EnhancedInputComponent->BindAction(SwapCharacter3, ETriggerEvent::Triggered, this, &AShifterCharacter::HandleSwapCharacter);
		EnhancedInputComponent->BindAction(UseAbilityInput, ETriggerEvent::Triggered, this, &AShifterCharacter::HandleUseAbility);
	}
}

void AShifterCharacter::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AObstacle* CollidedObs = Cast<AObstacle>(OtherActor))
	{
		CollidedObs->OnPlayerCollided(this);
	}
}

// Called every frame
void AShifterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if((GetActorLocation() - TargetLocation).IsNearlyZero())
	{
		SetActorLocation(TargetLocation);
	}else
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, CurrentShapeType == EShapeType::Ball ? LaneSwapSpeedAsBall : LaneSwapSpeed));
	}
	if(bCanMove)
	{
		if(AShiftersGameMode* GameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
		{
			CurrentScore += (DeltaTime * GameMode->PlatformMovementSpeed * GameMode->PlayerScoreMultiplier);
		}
	}
	
}

AShifterSpawner* AShifterCharacter::GetSpawner()
{
	if(AShifterSpawner* Spawner = Cast<AShifterSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AShifterSpawner::StaticClass())))
	{
		return Spawner;
	}
	return nullptr;
}

void AShifterCharacter::StepLeft()
{
	if(LaneIndex > 0)
	{
		FVector Loc = GetActorLocation();
		Loc.Y = GetSpawner()->GetGridLocationByIndex(--LaneIndex).Y;
		TargetLocation = Loc;
	}
}

void AShifterCharacter::StepRight()
{
	if(LaneIndex < GetSpawner()->GridWidth-1)
	{
		FVector Loc = GetActorLocation();
		Loc.Y = GetSpawner()->GetGridLocationByIndex(++LaneIndex).Y;
		
		TargetLocation = Loc;
	}
}

float AShifterCharacter::GetPlayerHealth()
{
	return PlayerHealth;
}

float AShifterCharacter::GetPlayerHealthPercentage()
{
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		return PlayerHealth / ShiftersGameMode->PlayerMaxHealth;
	}
	return 0.f;
}

void AShifterCharacter::SetPlayerHealth(float Health)
{
	if(Health >= 0)
	{
		PlayerHealth = Health;
		if(PlayerHealth == 0)
		{
			if(AShifterPlayerController* PlayerController = Cast<AShifterPlayerController>(GetController()))
			{
				PlayerController->TriggerPlayerDeath();
			}
		}
	}
}

void AShifterCharacter::ChangePlayerHealth(float DeltaHealth)
{
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{

		if(DeltaHealth >= 0.f)
		{
			DeltaHealth = FMath::Clamp(PlayerHealth+DeltaHealth, 0, ShiftersGameMode->PlayerMaxHealth);
			SetPlayerHealth(DeltaHealth);
		}else
		{
			DeltaHealth *= -1.f;
			
			float TransferDamage = FMath::Max(0.f, DeltaHealth - ShieldCurrentHealth);
			bool bShouldDropPlayerDamage = ShieldCurrentHealth > 0.f && TransferDamage >= PlayerHealth;

			float ShieldTakeDamage = FMath::Min(ShieldCurrentHealth, DeltaHealth);
			ShieldCurrentHealth -= ShieldTakeDamage;

			if(!bShouldDropPlayerDamage)
			{
				DeltaHealth = FMath::Clamp(PlayerHealth-TransferDamage, 0.f, ShiftersGameMode->PlayerMaxHealth);
				SetPlayerHealth(DeltaHealth);
			}
			
		}
	}
}

void AShifterCharacter::ToggleSideMovement(bool bOn)
{
	bCanMove = bOn;
}

EShapeType AShifterCharacter::GetShapeType()
{
	return CurrentShapeType;
}

void AShifterCharacter::SetShapeType(EShapeType ToSet)
{
	CurrentShapeType = ToSet;
}

void AShifterCharacter::OnPlayerShifted(EShapeType Shape)
{
	
}

void AShifterCharacter::ActivateShield()
{
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ShieldCurrentHealth = ShiftersGameMode->ShieldMaxHealth;
	}
}

void AShifterCharacter::DeactivateShield()
{
	ShieldCurrentHealth = 0.f;
}

float AShifterCharacter::GetShieldPercentage()
{
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		return ShieldCurrentHealth / ShiftersGameMode->ShieldMaxHealth;
	}
	return 0.f;
}

float AShifterCharacter::GetShieldHealth()
{
	return ShieldCurrentHealth;
}

