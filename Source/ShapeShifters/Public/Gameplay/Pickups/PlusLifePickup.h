// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Pickups/Pickup.h"
#include "PlusLifePickup.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API APlusLifePickup : public APickup
{
	GENERATED_BODY()

public:

	virtual void ActivateImmediateEffect(AShifterCharacter* Character) override;
	
};
