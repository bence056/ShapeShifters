// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Pickups/Pickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API AHealthPickup : public APickup
{
	GENERATED_BODY()

public:

	AHealthPickup();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float HealAmount;

	virtual void OnPickupTriggered(AShifterCharacter* Character) override;
	
};
