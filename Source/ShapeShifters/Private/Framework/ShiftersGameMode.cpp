// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Framework/ShiftersGameMode.h"

#include "Framework/ShifterPlayerController.h"
#include "Gameplay/Abilities/Ability.h"
#include "Gameplay/Player/ShifterCharacter.h"
#include "Gameplay/Powerups/Powerup.h"

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
	GameCharacterPtr = nullptr;
	PickupMaxSpawnTrials = 2;
}

void AShiftersGameMode::ShiftPlayer(AShifterCharacter* Player, EShapeType ToShape)
{
	if(Player->GetShapeType() != ToShape && Player->CanCharacterMove())
	{
		
		//cancel the ability:
		if(UAbility** Ability = ShapeAbilityTable.Find(Player->GetShapeType()))
		{
			(*Ability)->ExpireAbility(Player);
		}
		Player->SetShapeType(ToShape);
		if(UStaticMesh** NewShape = ShapeMeshTable.Find(ToShape))
		{
			Player->ShapeMesh->SetStaticMesh(*NewShape);
		}
		Player->OnPlayerShifted(ToShape);
	}
	
}

void AShiftersGameMode::CreateAndAssignPowerup(EPickupTypes Powerup)
{
	for(auto& Pwr : ActivePowerups)
	{
		if(Pwr->PowerupType == Powerup)
		{
			//restart
			Pwr->RestartPowerup();
			return;
		}
	}
	if(TSubclassOf<UPowerup>* PowerupClass = PowerupClasses.Find(Powerup))
	{
		UPowerup* PowerupObj = NewObject<UPowerup>(GameCharacterPtr, *PowerupClass);
		PowerupObj->OnPowerupActivated();
		ActivePowerups.Add(PowerupObj);
		if(AShifterPlayerController* ShifterPlayerController = Cast<AShifterPlayerController>(GameCharacterPtr->GetController()))
		{
			ShifterPlayerController->UpdatePowerupsVisual();
		}
	}
}

void AShiftersGameMode::NotifyPowerupExpired(UPowerup* Powerup)
{
	if(ActivePowerups.Contains(Powerup))
	{
		ActivePowerups.Remove(Powerup);
		if(AShifterPlayerController* ShifterPlayerController = Cast<AShifterPlayerController>(GameCharacterPtr->GetController()))
		{
			ShifterPlayerController->UpdatePowerupsVisual();
		}
	}
}

void AShiftersGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	PlatformMovementSpeed += DeltaSeconds * PlatformAcceleration;
}
