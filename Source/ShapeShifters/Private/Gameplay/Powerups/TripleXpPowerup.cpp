// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Powerups/TripleXpPowerup.h"

#include "Framework/ShifterPlayerController.h"
#include "Framework/ShiftersGameMode.h"

void UTripleXpPowerup::OnPowerupActivated()
{
	Super::OnPowerupActivated();
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ShiftersGameMode->PlayerScoreMultiplier *= 3.f;
	}
}

void UTripleXpPowerup::OnPowerupExpired()
{
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ShiftersGameMode->PlayerScoreMultiplier /= 3.f;
	}
	Super::OnPowerupExpired();
}
