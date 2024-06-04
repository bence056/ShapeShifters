// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/World/PlatformSpawner.h"

#include "Components/BoxComponent.h"
#include "Gameplay/World/Platform.h"


// Sets default values
APlatformSpawner::APlatformSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SetRootComponent(SpawnArea);
	SpawnArea->OnComponentEndOverlap.AddDynamic(this, &APlatformSpawner::EndOverlap);
	SpawnArea->OnComponentBeginOverlap.AddDynamic(this, &APlatformSpawner::BeginOverlap);
	
}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformSpawner::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(APlatform* PlatformActor = Cast<APlatform>(OtherActor))
	{
		if(PlatformsInArea.Contains(PlatformActor))
		{
			PlatformsInArea.Remove(PlatformActor);
		}
	}
}

void APlatformSpawner::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(APlatform* PlatformActor = Cast<APlatform>(OtherActor))
	{
		if(!PlatformsInArea.Contains(PlatformActor))
		{
			// PlatformsInArea.Add(PlatformActor);
		}
	}
}

// Called every frame
void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//spawn platforms

	if(PlatformClasses.Num() == 0) return;

	TSubclassOf<APlatform> PlatformClass = AActor::StaticClass();
	TArray<float> Weights;
	PlatformClasses.GenerateValueArray(Weights);
	float SumWeight = 0;
	for (auto Weight : Weights) SumWeight+=Weight;
	float RandW = FMath::RandRange(0.f, SumWeight);
	for(auto& Pair : PlatformClasses.Array())
	{
		if(RandW < Pair.Value)
		{
			PlatformClass = Pair.Key;
			break;
		}
		RandW -= Pair.Value;
	}
	
	if(PlatformClass && PlatformsInArea.Num() < MaxPlatformCount)
	{
		FVector SpawnLoc = GetActorLocation();
		SpawnLoc.X -= SpawnArea->GetScaledBoxExtent().X;
		//set the spawn loc to the last platforms edge if exists:
		if(PlatformsInArea.Num() > 0)
		{
			SpawnLoc = PlatformsInArea[PlatformsInArea.Num()-1]->GetActorLocation();
			SpawnLoc.X += 3100.f;
		}

		//spawn the platform
		APlatform* Platform = GetWorld()->SpawnActor<APlatform>(PlatformClass, SpawnLoc, FRotator::ZeroRotator);
		if(PlatformsInArea.Num() >= 1)
		{
			Platform->LinkedPlatform = PlatformsInArea[PlatformsInArea.Num()-1];
		}
		PlatformsInArea.Add(Platform);
		Platform->GeneratePlatformContents();
		
	}
	
}

