// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Gameplay/Player/ShifterCharacter.h"

#include "Gameplay/Player/GameCamera.h"
#include "Gameplay/World/ShifterSpawner.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AShifterCharacter::AShifterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	ShapeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShapeMesh"));
	ShapeMesh->SetupAttachment(GetRootComponent());
	LaneIndex = 0;
}

// Called when the game starts or when spawned
void AShifterCharacter::BeginPlay()
{
	Super::BeginPlay();
	TargetLocation = GetActorLocation();
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

void AShifterCharacter::SetCameraActor(AGameCamera* Cam)
{
	ControllingCamera = Cam;
}

void AShifterCharacter::StepLeft()
{
	if(LaneIndex > 0)
	{
		FVector Loc = GetActorLocation();
		Loc.Y = ControllingCamera->GetSpawner()->GetGridLocationByIndex(--LaneIndex).Y;
		TargetLocation = Loc;
	}
}

void AShifterCharacter::StepRight()
{
	if(LaneIndex < ControllingCamera->GetSpawner()->GridWidth-1)
	{
		FVector Loc = GetActorLocation();
		Loc.Y = ControllingCamera->GetSpawner()->GetGridLocationByIndex(++LaneIndex).Y;
		
		TargetLocation = Loc;
	}
}

