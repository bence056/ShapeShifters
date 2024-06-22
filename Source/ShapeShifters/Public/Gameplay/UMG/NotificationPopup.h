// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationPopup.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API UNotificationPopup : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	FText MessageText;
	
	UFUNCTION(BlueprintImplementableEvent)
	void TriggerPopup();
	
};
