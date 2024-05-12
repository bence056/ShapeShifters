// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/World/Platform.h"

#include "Framework/ShiftersGameMode.h"
#include "Gameplay/Obstacles/Obstacle.h"
#include "Kismet/GameplayStatics.h"


FGridData::FGridData()
{
	CellX = 0;
	CellY = 0;
	ContainedObstacle = nullptr;
}

// Sets default values
APlatform::APlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	MaxSpawnTrials = 5;
}

// Called when the game starts or when spawned
void APlatform::BeginPlay()
{
	Super::BeginPlay();

	if(AShiftersGameMode* GMode = Cast<AShiftersGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		Speed = GMode->PlatformMovementSpeed;
	}
	
}

void APlatform::FellOutOfWorld(const UDamageType& dmgType)
{
	UE_LOG(LogTemp, Warning,TEXT("KILLL"));
	Super::FellOutOfWorld(dmgType);
}

FVector APlatform::GetGridLocation(int32 X, int32 Y)
{
	FVector Loc = GetActorLocation();
	//get bottom left corner.
	Loc -= FVector(1,1,0) * 1500.f;
	float CellSize = 3000.f / 8.f;
	//adjust to center.
	Loc += FVector(CellSize/2, CellSize/2, 0.f);
	//select the grid.
	Loc += FVector(X*CellSize, Y*CellSize, 0.f);
	return Loc;
}

// Called every frame
void APlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(GetActorLocation() + FVector(-1.f, 0.f, 0.f) * DeltaTime * Speed);
	
}

void APlatform::DestroyPlatformAndContents()
{
	Destroy();
}

void APlatform::GeneratePlatformContents()
{
	for(int i=0; i<MaxSpawnTrials; i++)
	{
		TArray<EPlatformContentTypes> PlatformContentTypes;
		ObstacleClasses.GetKeys(PlatformContentTypes);
		if(PlatformContentTypes.Num() > 0)
		{
			int32 RandomSelect = FMath::RandRange(0, PlatformContentTypes.Num()-1);
			EPlatformContentTypes Type = PlatformContentTypes[RandomSelect];

			//spawn wall cuz why not.
			Type = EPlatformContentTypes::Wall;
			if(Type == EPlatformContentTypes::Wall)
			{
				//select a row to spawn the wall in.
				int32 RowCount = FMath::RandRange(0, 7);
				//select a start and an end cell.
				int32 StartCell = FMath::RandRange(0, 7);
				int32 EndCell = FMath::RandRange(0, 7);

				//Generate Wall.
				int32 ArrayStart = FMath::Min(StartCell, EndCell);
				int32 ArrayEnd = FMath::Max(StartCell, EndCell);
				
				for(int32 j=ArrayStart; j<=ArrayEnd; j++)
				{
					AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(*ObstacleClasses.Find(Type), GetGridLocation(RowCount, j), FRotator::ZeroRotator);
					Obstacle->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				}
				break;
			}
		
		}
	}
}

