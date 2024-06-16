// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Framework/ShiftersGameMode.h"

#include "Gameplay/Player/ShifterCharacter.h"

AShiftersGameMode::AShiftersGameMode()
{
	PlatformMovementSpeed = 100.f;
	MinimumWallGap = 2;
	MaxObstacleReplacementTrials = 3;
	MaxWallSpawnTrials = 3;
	MinimumWallWidth = 1;
	MaximumWallWidth = 8;
	ShiftTokens = 50;
}

void AShiftersGameMode::ShiftPlayer(AShifterCharacter* Player, EShapeType ToShape)
{
	if(Player->GetShapeType() != ToShape)
	{
		if(ShiftTokens > 0)
		{
			Player->SetShapeType(ToShape);
			ShiftTokens--;
			if(UStaticMesh* NewShape = *ShapeMeshTable.Find(ToShape))
			{
				Player->ShapeMesh->SetStaticMesh(NewShape);
			}
			Player->OnPlayerShifted(ToShape);
		}
	}
}

void AShiftersGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	PlatformMovementSpeed += DeltaSeconds * PlatformAcceleration;
}
