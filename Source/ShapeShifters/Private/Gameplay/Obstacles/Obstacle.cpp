// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Obstacles/Obstacle.h"

#include "Gameplay/Player/ShifterCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AObstacle::AObstacle(): PosX(0), PosY(0), ObstacleType(EPlatformContentTypes::None)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OwningPlatform = nullptr;
	DamageToDeal = 0;
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
}



void AObstacle::OnPlayerCollided(AShifterCharacter* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Collided with: %s"), *GetName());
	//deal damage.

	//do all sorts of magic:

	switch (Player->GetShapeType()) {
	case EShapeType::Cube:
		if(ObstacleType == EPlatformContentTypes::Breakable) DamageToDeal*=0.7f;
		break;
	case EShapeType::Ball:
		break;
	case EShapeType::Cylinder:
		if(ObstacleType == EPlatformContentTypes::Spike) DamageToDeal*=0.7f;
		break;
	case EShapeType::Pyramid:
		if(ObstacleType == EPlatformContentTypes::Laser) DamageToDeal*=0.7f;
		break;
	case EShapeType::Octahedron:
		break;
	case EShapeType::Dodecahedron:
		break;
	case EShapeType::MobiusStrip:
		break;
	}
	
	Player->ChangePlayerHealth(-DamageToDeal);
}

