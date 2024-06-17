// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShifterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API UShifterGameInstance : public UGameInstance
{
	GENERATED_BODY()


	
public:

	UShifterGameInstance();
	
	UPROPERTY(BlueprintReadOnly)
	float HighScore;
	
};
