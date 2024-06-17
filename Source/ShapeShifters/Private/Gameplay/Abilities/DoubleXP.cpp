// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/DoubleXP.h"

#include "Framework/ShiftersGameMode.h"

UDoubleXP::UDoubleXP()
{
	XpMultipler = 2.f;
}

void UDoubleXP::OnAbilityActivated(AShifterCharacter* PlayerCharacter)
{
	Super::OnAbilityActivated(PlayerCharacter);
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ShiftersGameMode->PlayerScoreMultiplier *= XpMultipler;
	}
}

void UDoubleXP::OnAbilityExpired(AShifterCharacter* PlayerCharacter)
{
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ShiftersGameMode->PlayerScoreMultiplier /= XpMultipler;
	}
	Super::OnAbilityExpired(PlayerCharacter);
}
