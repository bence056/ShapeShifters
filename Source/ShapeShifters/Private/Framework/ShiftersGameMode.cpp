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
	bCheckpointPaused = true;
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

void AShiftersGameMode::EquipShape(EShapeType Type)
{
	if(UnlockedShapes.Contains(Type))
	{
		if(!ShapeLoadout.Contains(Type))
		{
			ShapeLoadout.Add(Type);
			if(UAbility** Ability = ShapeAbilityTable.Find(Type))
			{
				(*Ability)->ResetAbility();
			}
		}
	}
}

void AShiftersGameMode::UnequipShape(EShapeType Type)
{
	if(UnlockedShapes.Contains(Type))
	{
		if(ShapeLoadout.Contains(Type))
		{
			ShapeLoadout.Remove(Type);
		}
	}
}

void AShiftersGameMode::PauseAtCheckpoint(bool bPause)
{
	bCheckpointPaused = bPause;

	if(bCheckpointPaused)
	{
		for(auto& Ability : ShapeAbilityTable)
		{
			Ability.Value->ExpireAbility(GameCharacterPtr);
			Ability.Value->DisableCharging();
		}
		for(auto& Powerup : ActivePowerups)
		{
			Powerup->OnPowerupExpired();
		}
	}else
	{
		for(auto& Ability : ShapeAbilityTable)
		{
			Ability.Value->EnableCharging();
		}
		ShiftPlayer(GameCharacterPtr, ShapeLoadout[0]);
	}
	
	if(AShifterPlayerController* ShifterPlayerController = Cast<AShifterPlayerController>(GameCharacterPtr->GetController()))
	{
		ShifterPlayerController->TriggerCheckpointPaused(bPause);
	}
}

float AShiftersGameMode::GetPlatformSpeed()
{
	if(!bCheckpointPaused)
	{
		return PlatformMovementSpeed;
	}
	return 0.f;
	
}

void AShiftersGameMode::SetPlatformSpeed(float Speed)
{
	PlatformMovementSpeed = Speed;
}


void AShiftersGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(!bCheckpointPaused)
	{
		PlatformMovementSpeed += DeltaSeconds * PlatformAcceleration;
	}
}
