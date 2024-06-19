// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Pickups/HealthPickup.h"
#include "Gameplay/Player/ShifterCharacter.h"

AHealthPickup::AHealthPickup()
{
	HealAmount = 20.f;
}

void AHealthPickup::ActivateImmediateEffect(AShifterCharacter* Character)
{
	Character->ChangePlayerHealth(HealAmount);
	Super::ActivateImmediateEffect(Character);
}
