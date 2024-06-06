// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShiftersGameMode.generated.h"

class AObstacle;
enum class EPlatformContentTypes : uint8;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EPlatformContentTypes, TSubclassOf<AObstacle>> ObstacleClasses;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EPlatformContentTypes, float> ObstacleWeights;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxWallSpawnTrials;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxObstacleReplacementTrials;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MinimumWallGap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MinimumWallWidth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaximumWallWidth;
	
};
