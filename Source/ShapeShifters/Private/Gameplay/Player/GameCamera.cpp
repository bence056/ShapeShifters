// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Gameplay/Player/GameCamera.h"

#include "Camera/CameraComponent.h"


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

