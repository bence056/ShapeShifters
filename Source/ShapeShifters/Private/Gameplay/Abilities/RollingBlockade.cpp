// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/RollingBlockade.h"

#include "Gameplay/Player/ShifterCharacter.h"

void URollingBlockade::OnAbilityActivated(AShifterCharacter* PlayerCharacter)
{
	Super::OnAbilityActivated(PlayerCharacter);
	PlayerCharacter->ActivateShield();
}

void URollingBlockade::OnAbilityExpired(AShifterCharacter* PlayerCharacter)
{
	PlayerCharacter->DeactivateShield();
	Super::OnAbilityExpired(PlayerCharacter);
}
