// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Gameplay/Player/ShifterCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Framework/ShifterPlayerController.h"
#include "Framework/ShiftersGameMode.h"
#include "Gameplay/Obstacles/Obstacle.h"
#include "Gameplay/World/ShifterSpawner.h"
#include "Kismet/GameplayStatics.h"


class UEnhancedInputLocalPlayerSubsystem;
// Sets default values
AShifterCharacter::AShifterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	// SetRootComponent(RootComp);
	ObstacleCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(ObstacleCollisionBox);
	ObstacleCollisionBox->SetGenerateOverlapEvents(true);
	ShapeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShapeMesh"));
	ShapeMesh->SetupAttachment(GetRootComponent());
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	ViewCamera->SetupAttachment(GetRootComponent());
	LaneIndex = 0;
}

// Called when the game starts or when spawned
void AShifterCharacter::BeginPlay()
{
	Super::BeginPlay();
	TargetLocation = GetActorLocation();
	ObstacleCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShifterCharacter::OnCollision);
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
	float InputData = Action.GetValue().Get<float>();
	if(InputData < 0.f)
	{
		StepLeft();
		
	}else if(InputData > 0.f)
	{
		StepRight();
	}
}

void AShifterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LaneChangeInputLeft, ETriggerEvent::Triggered, this, &AShifterCharacter::HandleLaneMovement);
		EnhancedInputComponent->BindAction(LaneChangeInputRight, ETriggerEvent::Triggered, this, &AShifterCharacter::HandleLaneMovement);
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
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, 8.f));
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
		DeltaHealth = FMath::Clamp(PlayerHealth+DeltaHealth, 0, ShiftersGameMode->PlayerMaxHealth);
		SetPlayerHealth(DeltaHealth);
	}
}

