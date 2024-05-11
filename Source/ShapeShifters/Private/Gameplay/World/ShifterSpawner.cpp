// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Gameplay/World/ShifterSpawner.h"

#include "Components/BoxComponent.h"


// Sets default values
AShifterSpawner::AShifterSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GridWidth = 8;
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
}

// Called when the game starts or when spawned
void AShifterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AShifterSpawner::GetGridLocationByIndex(int32 Index)
{
	FVector BoxSize = SpawnBox->GetScaledBoxExtent() * 2.f;
	FVector BoxLeftSide = SpawnBox->GetComponentLocation() - BoxSize / 2;
	float CellWidth = BoxSize.Y / GridWidth;
	
	if(Index >= 0 && Index < GridWidth)
	{
		FVector ReturnVector = BoxLeftSide + Index * CellWidth + CellWidth/2;
		ReturnVector.X = GetActorLocation().X;
		ReturnVector.Z = GetActorLocation().Z;
		return ReturnVector;
	}
	return FVector::Zero();
}

// Called every frame
void AShifterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

