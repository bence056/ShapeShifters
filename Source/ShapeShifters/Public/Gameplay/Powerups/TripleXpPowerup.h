// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Powerups/Powerup.h"
#include "TripleXpPowerup.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API UTripleXpPowerup : public UPowerup
{
	GENERATED_BODY()

public:

	virtual void OnPowerupActivated() override;
	virtual void OnPowerupExpired() override;
	
};
