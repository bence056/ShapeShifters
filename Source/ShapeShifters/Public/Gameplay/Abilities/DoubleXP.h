// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "DoubleXP.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API UDoubleXP : public UAbility
{
	GENERATED_BODY()

public:

	UDoubleXP();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float XpMultipler;

	virtual void OnAbilityActivated(AShifterCharacter* PlayerCharacter) override;
	virtual void OnAbilityExpired(AShifterCharacter* PlayerCharacter) override;
	
};
