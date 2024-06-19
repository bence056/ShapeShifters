// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Powerups/Powerup.h"
#include "ClockworkPowerup.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API UClockworkPowerup : public UPowerup
{
	GENERATED_BODY()

public:


	UClockworkPowerup();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float NewTimeDilatation;

	virtual void OnPowerupActivated() override;
	virtual void OnPowerupExpired() override;

	
	
};
