// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Abilities/Ability.h"
#include "BarrierBash.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API UBarrierBash : public UAbility
{
	GENERATED_BODY()

public:

	virtual void OnAbilityActivated(AShifterCharacter* PlayerCharacter) override;
	
};
