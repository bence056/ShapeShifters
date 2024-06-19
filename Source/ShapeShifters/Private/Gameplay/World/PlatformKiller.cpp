// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/World/PlatformKiller.h"

#include "Components/BoxComponent.h"
#include "Gameplay/World/Platform.h"


// Sets default values
APlatformKiller::APlatformKiller()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KillArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SetRootComponent(KillArea);
	KillArea->OnComponentBeginOverlap.AddDynamic(this, &APlatformKiller::BeginOverlap);
	
}

// Called when the game starts or when spawned
void APlatformKiller::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformKiller::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for(auto& KC : KillClasses)
	{
		if(OtherActor->GetClass()->IsChildOf(KC))
		{
			OtherActor->Destroy();
		}
	}
	
}

// Called every frame
void APlatformKiller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

