// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/Ability.h"

#include "Framework/ShiftersGameMode.h"

class AShiftersGameMode;

UAbility::UAbility(): AbilityChargeTime(5), bTimeBased(true), AbilityRunTime(10), StackMax(1), bCanCharge(true), StackCurrent(0)
{
}

void UAbility::ActiveTimerExpiredCallback()
{
	if(AShiftersGameMode* GameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ExpireAbility(GameMode->GameCharacterPtr);
	}
}

void UAbility::ChargeTimerExpiredCallback()
{
	StackCurrent++;
	if(StackCurrent < StackMax)
	{
		InitializeAbility(false);
	}
}

void UAbility::ActivateAbility(AShifterCharacter* PlayerCharacter)
{
	if(StackCurrent > 0 && !GetWorld()->GetTimerManager().IsTimerActive(ActiveTimer))
	{
		DisableCharging();
		if(bTimeBased)
		{
			GetWorld()->GetTimerManager().SetTimer(ActiveTimer, this, &UAbility::ActiveTimerExpiredCallback, AbilityRunTime);
		}else
		{
			EnableCharging();
		}
		StackCurrent--;
		OnAbilityActivated(PlayerCharacter);
	}
	
}

void UAbility::ExpireAbility(AShifterCharacter* PlayerCharacter)
{
	if(IsAbilityActive())
	{
		GetWorld()->GetTimerManager().ClearTimer(ActiveTimer);
		EnableCharging();
	}
	OnAbilityExpired(PlayerCharacter);
}

void UAbility::OnAbilityActivated(AShifterCharacter* PlayerCharacter)
{
}

void UAbility::OnAbilityExpired(AShifterCharacter* PlayerCharacter)
{
}

float UAbility::GetAbilityChargePercent()
{
	return FMath::Max(0, GetWorld()->GetTimerManager().GetTimerElapsed(ChargeTimer)) / AbilityChargeTime;	
}

float UAbility::GetAbilityRunPercent()
{
	if(bTimeBased)
	{
		return FMath::Max(0, GetWorld()->GetTimerManager().GetTimerElapsed(ActiveTimer)) / AbilityRunTime;	
	}
	return 0;
}

void UAbility::InitializeAbility(bool bInstantAvailable, int32 SetStack)
{
	if(!bInstantAvailable)
	{
		GetWorld()->GetTimerManager().SetTimer(ChargeTimer, this, &UAbility::ChargeTimerExpiredCallback, AbilityChargeTime);
		if(!bCanCharge) GetWorld()->GetTimerManager().PauseTimer(ChargeTimer);
	}else
	{
		this->StackCurrent = SetStack;
	}
}

void UAbility::EnableCharging()
{
	bCanCharge = true;
	if(GetWorld()->GetTimerManager().IsTimerPaused(ChargeTimer))
	{
		GetWorld()->GetTimerManager().UnPauseTimer(ChargeTimer);
	}else
	{
		//start a new timer;
		InitializeAbility(false);
	}
}

void UAbility::DisableCharging()
{
	bCanCharge = false;
	if(GetWorld()->GetTimerManager().IsTimerActive(ChargeTimer))
	{
		GetWorld()->GetTimerManager().PauseTimer(ChargeTimer);
	}
}

bool UAbility::IsAbilityActive()
{
	return GetWorld()->GetTimerManager().IsTimerActive(ActiveTimer);
}
