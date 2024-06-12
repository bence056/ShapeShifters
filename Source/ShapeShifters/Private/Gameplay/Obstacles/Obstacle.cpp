// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Obstacles/Obstacle.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AObstacle::AObstacle(): PosX(0), PosY(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bShouldSlide = false;
	HideSlideDistance = 1000.f;
	OwningPlatform = nullptr;
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bShouldSlide)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *((GetActorLocation()-SlideTargetLoc)*FVector(0.f,0.f,1.f)).ToString());
		if(((GetActorLocation()-SlideTargetLoc)*FVector(0.f,0.f,1.f)).IsNearlyZero())
		{
			bShouldSlide = false;
		}
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), SlideTargetLoc, DeltaTime, 6.f));
	}
}

void AObstacle::TriggerSlide()
{
	SlideTargetLoc = GetActorLocation() - FVector(0.f, 0.f, HideSlideDistance);
	bShouldSlide = true;
}

void AObstacle::OnPlayerCollided(AShifterCharacter* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Collided with: %s"), *GetName());
}

