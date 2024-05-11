// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Gameplay/Player/GameCamera.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Gameplay/Player/ShifterCharacter.h"
#include "Gameplay/World/ShifterSpawner.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGameCamera::AGameCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	ViewCamera->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LaneChangeInputLeft, ETriggerEvent::Triggered, this, &AGameCamera::HandleLaneMovement);
		EnhancedInputComponent->BindAction(LaneChangeInputRight, ETriggerEvent::Triggered, this, &AGameCamera::HandleLaneMovement);
	}
	
}

void AGameCamera::SetControlledPlayer(AShifterCharacter* Player)
{
	ControlledPlayer = Player;
	ControlledPlayer->SetCameraActor(this);
}

AShifterSpawner* AGameCamera::GetSpawner()
{
	if(AShifterSpawner* Spawner = Cast<AShifterSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AShifterSpawner::StaticClass())))
	{
		return Spawner;
	}
	return nullptr;
}

void AGameCamera::PawnClientRestart()
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

void AGameCamera::HandleLaneMovement(const FInputActionInstance& Action)
{
	float InputData = Action.GetValue().Get<float>();
	if(InputData < 0.f)
	{
		ControlledPlayer->StepLeft();
		
	}else if(InputData > 0.f)
	{
		ControlledPlayer->StepRight();
	}
	
}
