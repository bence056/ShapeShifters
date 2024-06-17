// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Framework/ShiftersGameMode.h"

#include "Gameplay/Abilities/Ability.h"
#include "Gameplay/Player/ShifterCharacter.h"

AShiftersGameMode::AShiftersGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	PlatformMovementSpeed = 100.f;
	MinimumWallGap = 2;
	MaxObstacleReplacementTrials = 3;
	MaxWallSpawnTrials = 3;
	MinimumWallWidth = 1;
	MaximumWallWidth = 8;
	ShiftTokens = 50;
	GameCharacterPtr = nullptr;
}

void AShiftersGameMode::ShiftPlayer(AShifterCharacter* Player, EShapeType ToShape)
{
	if(Player->GetShapeType() != ToShape)
	{
		if(ShiftTokens > 0)
		{
			//cancel the ability:
			if(UAbility** Ability = ShapeAbilityTable.Find(Player->GetShapeType()))
			{
				(*Ability)->ExpireAbility(Player);
			}
			Player->SetShapeType(ToShape);
			ShiftTokens--;
			if(UStaticMesh** NewShape = ShapeMeshTable.Find(ToShape))
			{
				Player->ShapeMesh->SetStaticMesh(*NewShape);
			}
			Player->OnPlayerShifted(ToShape);
		}
	}
}

void AShiftersGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	PlatformMovementSpeed += DeltaSeconds * PlatformAcceleration;
	// UE_LOG(LogTemp, Warning, TEXT("%f"), PlatformMovementSpeed);
}
