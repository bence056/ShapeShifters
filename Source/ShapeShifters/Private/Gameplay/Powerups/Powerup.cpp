// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Powerups/Powerup.h"

#include "Framework/ShiftersGameMode.h"
#include "Gameplay/Pickups/Pickup.h"

UPowerup::UPowerup()
{
	PowerupType = EPickupTypes::None;
	PowerupTime = 1.f;
	PowerupName = FText::FromString("Powerup");
	
}

void UPowerup::OnPowerupActivated()
{
	RestartPowerup();
	//let overrides do the rest.
}

void UPowerup::OnPowerupExpired()
{
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ShiftersGameMode->NotifyPowerupExpired(this);
	}
}

float UPowerup::GetPowerupTimePercent()
{
	if(GetWorld()->GetTimerManager().IsTimerActive(PowerupTimer))
	{
		return GetWorld()->GetTimerManager().GetTimerElapsed(PowerupTimer)/PowerupTime;
	}
	return 0;
}

void UPowerup::RestartPowerup()
{
	GetWorld()->GetTimerManager().SetTimer(PowerupTimer, this, &UPowerup::OnPowerupTimerExpired, PowerupTime);
}

void UPowerup::OnPowerupTimerExpired()
{
	OnPowerupExpired();
}
