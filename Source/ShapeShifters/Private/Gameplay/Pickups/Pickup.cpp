// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Pickups/Pickup.h"

#include "Gameplay/Player/ShifterCharacter.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(GetRootComponent());
	PickupMesh->SetGenerateOverlapEvents(true);

	PickupType = EPickupTypes::None;
	OwningPlatform = nullptr;
	PosX = 0;
	PosY = 0;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnPickupTriggered(AShifterCharacter* Character)
{
	Character->ChangePlayerHealth(20.f);
	Destroy();
}

