// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Abilities/Ability.h"
#include "RollingBlockade.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API URollingBlockade : public UAbility
{
	GENERATED_BODY()

public:

	virtual void OnAbilityActivated(AShifterCharacter* PlayerCharacter) override;
	virtual void OnAbilityExpired(AShifterCharacter* PlayerCharacter) override;
	
};
