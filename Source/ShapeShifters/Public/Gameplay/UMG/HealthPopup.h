// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthPopup.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API UHealthPopup : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DeltaHealth;

	UFUNCTION(BlueprintImplementableEvent)
	void TriggerPopup();
	
};
