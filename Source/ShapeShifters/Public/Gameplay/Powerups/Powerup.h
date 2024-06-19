// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Powerup.generated.h"

enum class EPickupTypes : uint8;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SHAPESHIFTERS_API UPowerup : public UObject
{
	GENERATED_BODY()

public:

	UPowerup();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EPickupTypes PowerupType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PowerupTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText PowerupName;


	UFUNCTION(BlueprintCallable)
	virtual void OnPowerupActivated();
	UFUNCTION(BlueprintCallable)
	virtual void OnPowerupExpired();

	UFUNCTION(BlueprintPure)
	float GetPowerupTimePercent();

	UFUNCTION(BlueprintCallable)
	void RestartPowerup();

protected:

	FTimerHandle PowerupTimer;

	UFUNCTION()
	void OnPowerupTimerExpired();
	
};
