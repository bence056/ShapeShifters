﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/World/Platform.h"

#include "Framework/ShifterGameInstance.h"
#include "Framework/ShiftersGameMode.h"
#include "Gameplay/Obstacles/Obstacle.h"
#include "Gameplay/Pickups/Pickup.h"
#include "Gameplay/Player/ShifterCharacter.h"
#include "Kismet/GameplayStatics.h"

FGridData::FGridData()
{
	CellX = 0;
	CellY = 0;
	ContainedObstacle = nullptr;
	ObstacleType = EPlatformContentTypes::None;
}

FPickupData::FPickupData()
{
	CellX = 0;
	CellY = 0;
	ContainedPickup = nullptr;
	PickupType = EPickupTypes::None;
}

// Sets default values
APlatform::APlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);
	bUseCustomSeed = false;
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
			GD.ObstacleType = EPlatformContentTypes::None;
			GridData.Add(GD);
			FPickupData PD = FPickupData();
			PD.CellX = x;
			PD.CellY = y;
			PD.ContainedPickup = nullptr;
			PD.PickupType = EPickupTypes::None;
			PickupGridData.Add(PD);
		}
	}
	//setup material

	// PlatformMesh->CreateAndSetMaterialInstanceDynamic(0);
	
	
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
		TgtGrid->ObstacleType = EPlatformContentTypes::None;
	}
	if(Type != EPlatformContentTypes::None)
	{
		if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
		{
			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(*ShiftersGameMode->ObstacleClasses.Find(Type), GetGridLocation(X, Y), FRotator::ZeroRotator);
			Obstacle->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			Obstacle->OwningPlatform = this;
			Obstacle->PosX = X;
			Obstacle->PosY = Y;
			Obstacle->ObstacleType = Type;
			SetDataAt(X, Y, Obstacle, Type);
		}
	}
}

void APlatform::SpawnPickup(EPickupTypes Type, int32 X, int32 Y)
{
	//delete alr existing obj.
	FPickupData* TgtGrid = GetPickupDataAt(X,Y);
	if(TgtGrid && TgtGrid->ContainedPickup)
	{
		TgtGrid->ContainedPickup->Destroy();
		TgtGrid->ContainedPickup = nullptr;
		TgtGrid->PickupType = EPickupTypes::None;
	}
	if(Type != EPickupTypes::None)
	{
		if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
		{
			APickup* Pickup = GetWorld()->SpawnActor<APickup>(*ShiftersGameMode->PickupClasses.Find(Type), GetGridLocation(X, Y), FRotator::ZeroRotator);
			Pickup->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			Pickup->OwningPlatform = this;
			Pickup->PosX = X;
			Pickup->PosY = Y;
			Pickup->PickupType = Type;
			SetPickupDataAt(X, Y, Pickup, Type);
		}
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

void APlatform::SetDataAt(int32 X, int32 Y, AObstacle* NewObstacle, EPlatformContentTypes Type)
{
	for(auto& Entry : GridData)
	{
		if(Entry.CellX == X && Entry.CellY == Y)
		{
			Entry.ContainedObstacle = NewObstacle;
			Entry.ObstacleType = Type;
		}
	}	
}

void APlatform::SetPickupDataAt(int32 X, int32 Y, APickup* NewPickup, EPickupTypes Type)
{
	for(auto& Entry : PickupGridData)
	{
		if(Entry.CellX == X && Entry.CellY == Y)
		{
			Entry.ContainedPickup = NewPickup;
			Entry.PickupType = Type;
		}
	}	
}

TArray<FGridData*> APlatform::GetCellsWithObstacle(EPlatformContentTypes Type)
{
	
	TArray<FGridData*> RetArray;
	for(auto& Cell : GridData)
	{
		if(Cell.ObstacleType == Type)
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

	if(AShiftersGameMode* GMode = Cast<AShiftersGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		SetActorLocation(GetActorLocation() + FVector(-1.f, 0.f, 0.f) * DeltaTime * GMode->GetPlatformSpeed());
	}

	// if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	// {
	// 	if(UShifterGameInstance* ShifterGameInstance = Cast<UShifterGameInstance>(GetGameInstance()))
	// 	{
	// 		PlatformMesh->SetScalarParameterValueOnMaterials("HSProgress", ShifterGameInstance->HighScore == 0 ? 0 : FMath::Clamp(ShiftersGameMode->GameCharacterPtr->CurrentScore / ShifterGameInstance->HighScore, 0, 1));
	// 	}
	// }
	
	
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
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		//phase 1:
		//generate the damn walls.


		
		FRandomStream RandStream = FRandomStream(CustomSeed);
		if(!bUseCustomSeed) RandStream.GenerateNewSeed();
		FRandomStream* Stream = &RandStream;

		if(bUseGlobalSeed)
		{
			Stream = &(ShiftersGameMode->GlobalRandomizer);
		}

		for(int32 Rep =0; Rep<ShiftersGameMode->MaxWallSpawnTrials; Rep++)
		{
			TArray<int32> PotentialRows;
			for(int32 i=0; i<8; i++)
			{
				if(!BlockedRows.Contains(i)) PotentialRows.Add(i);
			}
			if(PotentialRows.Num() > 0)
			{
				int32 SelectedRow = PotentialRows[Stream->RandRange(0, PotentialRows.Num()-1)];
				int32 SelectedWidth = Stream->RandRange(ShiftersGameMode->MinimumWallWidth, ShiftersGameMode->MaximumWallWidth);
				if(SelectedWidth >= 1)
				{
					int32 MaxWallColumn = 8-SelectedWidth;
					int32 StartingCol = Stream->RandRange(0, MaxWallColumn);
					
					for(int32 i=StartingCol; i<StartingCol+SelectedWidth; i++)
					{
						SpawnObstacle(EPlatformContentTypes::Wall, SelectedRow, i);
					}
					
					SetWallBlocks(SelectedRow);
					
					
				}
				
			}
			
		}
		
		//phase 2: gen obstacles.

		for(int32 i=0; i<ShiftersGameMode->MaxObstacleReplacementTrials; i++)
		{
			//select type;
			TArray<EPlatformContentTypes> Types;
			ShiftersGameMode->ObstacleClasses.GetKeys(Types);
			
			TMap<EPlatformContentTypes, float> FixedMap;
			for(auto& Pair : ShiftersGameMode->ObstacleWeights.Array())
			{
				//remove wall and any objects that dont have a spawnable actor assigned in the other map.
				if(Pair.Key != EPlatformContentTypes::Wall && Types.Contains(Pair.Key) || Pair.Key == EPlatformContentTypes::None)
				{
					FixedMap.Add(Pair);
				}
			}
			
			EPlatformContentTypes Type = EPlatformContentTypes::None;
			float SumWeight = 0;
			for(auto& Pair : FixedMap.Array()) SumWeight += Pair.Value;
			float RandomWeight = Stream->RandRange(0.f, SumWeight);
			for(auto& Pair : FixedMap.Array())
			{
				if(RandomWeight <= Pair.Value)
				{
					Type = Pair.Key;
					break;
				}
				RandomWeight -= Pair.Value;
			}
			
			TArray<FGridData*> AllowedGrids = GetAllowedWallReplacements(Type);
			if(AllowedGrids.Num() > 0)
			{
				FGridData* SelectedGrid = AllowedGrids[Stream->RandRange(0, AllowedGrids.Num()-1)];
				SpawnObstacle(Type, SelectedGrid->CellX, SelectedGrid->CellY);
			}
		}

		//phase 3: free up at least a single.

		for(int32 x=0; x<8; x++)
		{
			bool bShouldBreak = true;
			TArray<FGridData*> ToBreak;
			for(int32 y=0; y<8 && bShouldBreak; y++)
			{
				FGridData* Grid = GetCellDataAt(x,y);
				if(Grid->ObstacleType == EPlatformContentTypes::Wall || Grid->ObstacleType == EPlatformContentTypes::Turret)
				{
					if(Grid->ObstacleType == EPlatformContentTypes::Wall)
					{
						ToBreak.Add(Grid);
					}
				}else
				{
					bShouldBreak = false;
				}
			}
			if(bShouldBreak && ToBreak.Num() > 0)
			{
				FGridData* ReplaceGrid = ToBreak[Stream->RandRange(0, ToBreak.Num()-1)];
				SpawnObstacle(EPlatformContentTypes::None, ReplaceGrid->CellX, ReplaceGrid->CellY);
			}
		}

		//phase 4, orbs:


		for(int32 i=0; i<ShiftersGameMode->PickupMaxSpawnTrials; i++)
		{
			//select type;
			TArray<EPickupTypes> PickupTypes;
			ShiftersGameMode->PickupClasses.GetKeys(PickupTypes);
			
			//note: keep none as an option. it will allow us to give a chance to no pickup spawning on the platform.
		
			EPickupTypes PickupType = EPickupTypes::None;
			float SumWeight = 0;
			for(auto& Pair : ShiftersGameMode->PickupWeights.Array()) SumWeight += Pair.Value;
			float RandomWeight = Stream->RandRange(0.f, SumWeight);
			for(auto& Pair : ShiftersGameMode->PickupWeights.Array())
			{
				if(RandomWeight <= Pair.Value)
				{
					PickupType = Pair.Key;
					break;
				}
				RandomWeight -= Pair.Value;
			}
		
			TArray<TPair<int32, int32>> Empty = GetEmptyCells();
		
			if(ShiftersGameMode->PickupClasses.Contains(PickupType) && Empty.Num() > 0)
			{
				TPair<int32, int32> RandGrid = Empty[FMath::RandRange(0, Empty.Num()-1)];
				SpawnPickup(PickupType, RandGrid.Key, RandGrid.Value);
			}
		}
		
	}
}

void APlatform::SetWallBlocks(int32 NewWallRow)
{
	// add blocks;
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		for(int32 i=NewWallRow-ShiftersGameMode->MinimumWallGap; i<=NewWallRow+ShiftersGameMode->MinimumWallGap; i++)
		{
			if(i>=0 && i<=7)
			{
				if(!BlockedRows.Contains(i)) BlockedRows.Add(i);
			}else if(i>7)
			{
				if(!PreReservedRows.Contains(i)) PreReservedRows.Add(i);
			}
		}
	}
}

TArray<FGridData*> APlatform::GetAllowedWallReplacements(EPlatformContentTypes Type)
{
	TArray<FGridData*> ReturnGrid;
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		TArray<FGridData*> Data = GetCellsWithObstacle(EPlatformContentTypes::Wall);
		//get all surrounded walls.
		for(auto& D : Data)
		{
			bool bCanAdd = true;
			FGridData* CellLeft = D->CellY > 0 ? GetCellDataAt(D->CellX, D->CellY-1) : nullptr;
			FGridData* CellRight = D->CellY < 7 ? GetCellDataAt(D->CellX, D->CellY+1) : nullptr;

			if(Type == EPlatformContentTypes::None)
			{
				
				bCanAdd &= !CellLeft || CellLeft->ObstacleType == EPlatformContentTypes::Wall;
				bCanAdd &= !CellRight || CellRight->ObstacleType == EPlatformContentTypes::Wall;
			}else
			{
				if(D->CellY > 0 && D->CellY < 7)
				{

					if(Type == EPlatformContentTypes::Breakable)
					{
						bCanAdd &= CellLeft->ObstacleType == EPlatformContentTypes::Wall;
						bCanAdd &= CellRight->ObstacleType == EPlatformContentTypes::Wall;
					}else if(Type == EPlatformContentTypes::Laser)
					{
						bCanAdd &= CellLeft->ObstacleType == EPlatformContentTypes::Wall || CellLeft->ObstacleType == EPlatformContentTypes::Laser;
						bCanAdd &= CellRight->ObstacleType == EPlatformContentTypes::Wall || CellRight->ObstacleType == EPlatformContentTypes::Laser;
					}
					else if(Type == EPlatformContentTypes::Spike || Type == EPlatformContentTypes::Turret)
					{
						bCanAdd &= CellLeft->ObstacleType != EPlatformContentTypes::Breakable && CellLeft->ObstacleType != EPlatformContentTypes::Laser;
						bCanAdd &= CellRight->ObstacleType != EPlatformContentTypes::Breakable && CellRight->ObstacleType != EPlatformContentTypes::Laser;
					}
				}else
				{
					bCanAdd = false;
				}
			}
			if(bCanAdd) ReturnGrid.Add(D);
		}
	}
	return ReturnGrid;
}


TArray<TPair<int32, int32>> APlatform::GetEmptyCells()
{
	TArray<TPair<int32, int32>> EmptyAll;

	for(auto& GD : GetCellsWithObstacle(EPlatformContentTypes::None))
	{
		if(GetPickupDataAt(GD->CellX, GD->CellY)->PickupType == EPickupTypes::None)
		{
			EmptyAll.Add(TPair<int32, int32>(GD->CellX, GD->CellY));
		}
	}
	return EmptyAll;
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

FPickupData* APlatform::GetPickupDataAt(int32 X, int32 Y)
{
	for(auto& Cell : PickupGridData)
	{
		if(Cell.CellX == X && Cell.CellY == Y)
		{
			return &Cell;
		}
	}
	return nullptr;
}

