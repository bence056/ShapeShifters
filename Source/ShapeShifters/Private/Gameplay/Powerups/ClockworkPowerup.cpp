// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Powerups/ClockworkPowerup.h"

UClockworkPowerup::UClockworkPowerup()
{
	NewTimeDilatation = 0.5f;
}

void UClockworkPowerup::OnPowerupActivated()
{
	Super::OnPowerupActivated();
	UE_LOG(LogTemp, Warning, TEXT("aaaaa %f"), PowerupTime);
	GetWorld()->GetWorldSettings()->SetTimeDilation(NewTimeDilatation);
}

void UClockworkPowerup::OnPowerupExpired()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(1);
	Super::OnPowerupExpired();
}
