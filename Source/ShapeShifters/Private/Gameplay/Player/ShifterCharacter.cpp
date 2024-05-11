// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Gameplay/Player/ShifterCharacter.h"


// Sets default values
AShifterCharacter::AShifterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	ShapeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShapeMesh"));
	ShapeMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AShifterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShifterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

