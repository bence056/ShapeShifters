// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShiftersGameMode.generated.h"

class UAbility;
enum class EShapeType : uint8;
class AShifterCharacter;
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
	float PlatformAcceleration = 1;

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

	//player related stuff
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PlayerMaxHealth = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ShieldMaxHealth = 50;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PlayerScoreMultiplier = 0.003;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<EShapeType> ShapeLoadout;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EShapeType, UStaticMesh*> ShapeMeshTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
	TMap<EShapeType, UAbility*> ShapeAbilityTable;
	
	UFUNCTION(BlueprintCallable)
	void ShiftPlayer(AShifterCharacter* Player, EShapeType ToShape);

	UPROPERTY()
	AShifterCharacter* GameCharacterPtr;

protected:
	
	virtual void Tick(float DeltaSeconds) override;

	//game related stuff.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<EShapeType> UnlockedShapes;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ShiftTokens;
	
	
};
