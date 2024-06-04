// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/World/Platform.h"

#include "Framework/ShiftersGameMode.h"
#include "Gameplay/Obstacles/Obstacle.h"
#include "Gameplay/Obstacles/WallObstacle.h"
#include "Kismet/GameplayStatics.h"


FCellSpawnData::FCellSpawnData(): CellX(0), CellY(0), bRepeating(false), RepX(0), RepY(0),
                                  Type(EPlatformContentTypes::Wall)
{
}

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
	//delete alr existing obj.
	FGridData* TgtGrid = GetCellDataAt(X,Y);
	if(TgtGrid && TgtGrid->ContainedObstacle)
	{
		TgtGrid->ContainedObstacle->Destroy();
		TgtGrid->ContainedObstacle = nullptr;
	}
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(*ShiftersGameMode->ObstacleClasses.Find(Type), GetGridLocation(X, Y), FRotator::ZeroRotator);
		Obstacle->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		Obstacle->OwningPlatform = this;
		Obstacle->PosX = X;
		Obstacle->PosY = Y;
		SetDataAt(X, Y, Obstacle);
	}
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

TArray<FGridData*> APlatform::GetCellsWithObstacle(TSubclassOf<AObstacle> ClassFilter)
{
	TArray<FGridData*> RetArray;
	for(auto& Cell : GridData)
	{
		if(Cell.ContainedObstacle && Cell.ContainedObstacle->GetClass()->IsChildOf(ClassFilter))
		{
			RetArray.Add(&Cell);
		}
	}
	return RetArray;
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
	for(auto& Content : PlatformContent)
	{
		if(Content.bRepeating)
		{
			for(int32 x=Content.CellX; x<=Content.CellX + Content.RepX; x++)
			{
				for(int32 y=Content.CellY; y<=Content.CellY + Content.RepY; y++)
				{
					SpawnObstacle(Content.Type, x,y);
				}
			}
		}else
		{
			SpawnObstacle(Content.Type, Content.CellX, Content.CellY);
		}
		
	}
}

FGridData* APlatform::GetCellDataAt(int32 X, int32 Y)
{
	for(auto& Cell : GridData)
	{
		if(Cell.CellX == X && Cell.CellY == Y)
		{
			return &Cell;
		}
	}
	return nullptr;
}
