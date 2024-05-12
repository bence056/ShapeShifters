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

	for(int32 x=0; x<8; x++) {
		for(int32 y=0; y<8; y++)
		{
			FGridData GD = FGridData();
			GD.CellX = x;
			GD.CellY = y;
			GD.ContainedObstacle = nullptr;
			GridData.Add(GD);
		}
	}
	
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

void APlatform::SpawnObstacle(EPlatformContentTypes Type, int32 X, int32 Y)
{
	AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(*ObstacleClasses.Find(Type), GetGridLocation(X, Y), FRotator::ZeroRotator);
	Obstacle->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	SetDataAt(X, Y, Obstacle);
}

TArray<FGridData*> APlatform::GetEmptyInRow(int32 X)
{
	TArray<FGridData*> FreeCells;
	for(auto& Entry : GridData)
	{
		if(Entry.CellX == X && !Entry.ContainedObstacle)
		{
			FreeCells.Add(&Entry);
		}
	}
	return FreeCells;
}

bool APlatform::IsGridOccupiedAt(int32 X, int32 Y)
{
	for(auto& Entry : GridData)
	{
		if(Entry.CellX == X && Entry.CellY == Y)
		{
			return Entry.ContainedObstacle != nullptr;
		}
	}
	return false;
}

void APlatform::SetDataAt(int32 X, int32 Y, AObstacle* NewObstacle)
{
	for(auto& Entry : GridData)
	{
		if(Entry.CellX == X && Entry.CellY == Y)
		{
			Entry.ContainedObstacle = NewObstacle;
		}
	}	
}


// Called every frame
void APlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(GetActorLocation() + FVector(-1.f, 0.f, 0.f) * DeltaTime * Speed);
	
}

void APlatform::DestroyPlatformAndContents()
{
	for(auto& Entry : GridData)
	{
		if(Entry.ContainedObstacle)
		{
			Entry.ContainedObstacle->Destroy();
		}
	}
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

				TArray<FGridData*> FreeInRow = GetEmptyInRow(RowCount);

				//only allowed to spawn if there will be at least 1 gap.
				if(FreeInRow.Num() >= 2)
				{
					TArray<int32> PossibleWallStarts;
					for(auto& Free : FreeInRow)
					{
						PossibleWallStarts.Add(Free->CellY);
					}
					int32 StartCell = PossibleWallStarts[FMath::RandRange(0,PossibleWallStarts.Num()-1)];
					TArray<int32> PossibleWallEnds;
					//add the starting one (so we can and where we started);
					PossibleWallEnds.Add(StartCell);
					//check left:
					bool bFreeSlot = true;
					int32 locY = StartCell;
					//remaining free slots on the entire line (we added the start, so its -1)
					int32 FreeSlots = FreeInRow.Num()-1;
					while (bFreeSlot)
					{
						if(locY != 0)
						{
							//step one left.
							if(!IsGridOccupiedAt(RowCount, --locY) && FreeSlots > 1)
							{
								PossibleWallEnds.Add(locY);
								FreeSlots--;
							}else
							{
								bFreeSlot = false;
							}
						}else
						{
							bFreeSlot = false;
						}
					}
					//check right
					bFreeSlot = true;
					locY = StartCell;
					FreeSlots = FreeInRow.Num()-1;
					while (bFreeSlot)
					{
						if(locY != 7)
						{
							//step one right.
							if(!IsGridOccupiedAt(RowCount, ++locY) && FreeSlots > 1)
							{
								PossibleWallEnds.Add(locY);
								FreeSlots--;
							}else
							{
								bFreeSlot = false;
							}
						}else
						{
							bFreeSlot = false;
						}
					}
					int32 EndCell = PossibleWallEnds[FMath::RandRange(0, PossibleWallEnds.Num()-1)];

					for(auto& j : PossibleWallEnds)
					{
						UE_LOG(LogTemp, Warning, TEXT("%d"), j);
					}
					UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
					
					//Generate Wall.
				
					int32 ArrayStart = FMath::Min(StartCell, EndCell);
					int32 ArrayEnd = FMath::Max(StartCell, EndCell);
				
					for(int32 j=ArrayStart; j<=ArrayEnd; j++)
					{
						SpawnObstacle(Type, RowCount, j);
					}
				}
				
				
			}
		
		}
	}
}

