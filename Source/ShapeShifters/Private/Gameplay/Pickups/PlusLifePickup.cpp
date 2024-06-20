// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Pickups/PlusLifePickup.h"

#include "Gameplay/Player/ShifterCharacter.h"

void APlusLifePickup::ActivateImmediateEffect(AShifterCharacter* Character)
{
	Character->GrantExtraLife();
	Super::ActivateImmediateEffect(Character);
}
