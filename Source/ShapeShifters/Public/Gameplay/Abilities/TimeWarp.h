// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Abilities/Ability.h"
#include "TimeWarp.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API UTimeWarp : public UAbility
{
	GENERATED_BODY()

public:

	UTimeWarp();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PlatformSpeedMultiplier;

	virtual void OnAbilityActivated(AShifterCharacter* PlayerCharacter) override;
	virtual void OnAbilityExpired(AShifterCharacter* PlayerCharacter) override;


protected:

	UPROPERTY()
	float TempAccel;
	UPROPERTY()
	float TempSpeed;
	
};
