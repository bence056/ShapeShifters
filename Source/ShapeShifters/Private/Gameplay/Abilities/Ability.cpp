// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/Ability.h"

UAbility::UAbility(): AbilityChargeTime(5), bTimeBased(true), AbilityRunTime(10), StackCurrent(0), StackMax(1), bCanCharge(true)
{
}

void UAbility::ActiveTimerExpiredCallback()
{
	OnAbilityExpired();
}

void UAbility::ChargeTimerExpiredCallback()
{
	StackCurrent++;
	if(StackCurrent < StackMax)
	{
		InitializeAbility(false);
	}
}

void UAbility::OnAbilityActivated()
{
	if(StackCurrent > 0)
	{
		DisableCharging();
		if(bTimeBased)
		{
			GetWorld()->GetTimerManager().SetTimer(ActiveTimer, this, &UAbility::ActiveTimerExpiredCallback, AbilityRunTime);
		}
		StackCurrent--;
	}
	
}

void UAbility::OnAbilityExpired()
{
	EnableCharging();
	GetWorld()->GetTimerManager().ClearTimer(ActiveTimer);
	if(bCanCharge) InitializeAbility(false);
	
}

float UAbility::GetAbilityChargePercent()
{
	if(StackCurrent < StackMax)
	{
		return FMath::Max(0, GetWorld()->GetTimerManager().GetTimerElapsed(ChargeTimer)) / AbilityChargeTime;	
	}
	return 1;
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
