// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ability.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SHAPESHIFTERS_API UAbility : public UObject
{
	GENERATED_BODY()

public:

	UAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText AbilityName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AbilityChargeTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bTimeBased;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bTimeBased", EditConditionHides = true))
	float AbilityRunTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 StackMax;

	
protected:
	
	UPROPERTY()
	FTimerHandle ActiveTimer;
	UPROPERTY()
	FTimerHandle ChargeTimer;

	UFUNCTION()
	void ActiveTimerExpiredCallback();
	UFUNCTION()
	void ChargeTimerExpiredCallback();
	
	UPROPERTY()
	bool bCanCharge;
	UPROPERTY()
	int32 StackCurrent;
	
public:

	UFUNCTION()
	virtual void OnAbilityActivated();
	UFUNCTION()
	virtual void OnAbilityExpired();

	UFUNCTION(BlueprintPure)
	float GetAbilityChargePercent();
	UFUNCTION(BlueprintPure)
	float GetAbilityRunPercent();

	UFUNCTION()
	void InitializeAbility(bool bInstantAvailable, int32 SetStack = 0);

	UFUNCTION()
	void EnableCharging();
	UFUNCTION()
	void DisableCharging();
	
};
