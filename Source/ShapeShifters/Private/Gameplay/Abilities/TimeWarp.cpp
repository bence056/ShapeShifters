// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/TimeWarp.h"

#include "Framework/ShiftersGameMode.h"

UTimeWarp::UTimeWarp()
{
	TempAccel = 0.f;
	TempSpeed = 0.f;
	PlatformSpeedMultiplier = 0.5f;
}

void UTimeWarp::OnAbilityActivated(AShifterCharacter* PlayerCharacter)
{
	Super::OnAbilityActivated(PlayerCharacter);
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		TempAccel = ShiftersGameMode->PlatformAcceleration;
		TempSpeed = ShiftersGameMode->GetPlatformSpeed();
		ShiftersGameMode->PlatformAcceleration = 0.f;
		ShiftersGameMode->SetPlatformSpeed(ShiftersGameMode->GetPlatformSpeed() * PlatformSpeedMultiplier);
	}
}

void UTimeWarp::OnAbilityExpired(AShifterCharacter* PlayerCharacter)
{
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ShiftersGameMode->SetPlatformSpeed(TempSpeed);
		ShiftersGameMode->PlatformAcceleration = TempAccel;
	}
	Super::OnAbilityExpired(PlayerCharacter);
}
