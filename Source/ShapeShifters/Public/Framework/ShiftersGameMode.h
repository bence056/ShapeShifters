// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShiftersGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API AShiftersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AShiftersGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PlatformMovementSpeed;
	
};
