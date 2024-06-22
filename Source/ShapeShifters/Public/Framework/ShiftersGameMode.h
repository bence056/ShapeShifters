// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Gameplay/UMG/ShapeSlot.h"
#include "ShiftersGameMode.generated.h"

class UPowerup;
enum class EPickupTypes : uint8;
class APickup;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Platform")
	float PlatformAcceleration = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Obstacles")
	TMap<EPlatformContentTypes, TSubclassOf<AObstacle>> ObstacleClasses;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Obstacles")
	TMap<EPlatformContentTypes, float> ObstacleWeights;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Obstacles|Wall")
	int32 MaxWallSpawnTrials;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Obstacles")
	int32 MaxObstacleReplacementTrials;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Obstacles|Wall")
	int32 MinimumWallGap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Obstacles|Wall")
	int32 MinimumWallWidth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Obstacles|Wall")
	int32 MaximumWallWidth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickups")
	int32 PickupMaxSpawnTrials;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickups")
	TMap<EPickupTypes, TSubclassOf<APickup>> PickupClasses;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickups")
	TMap<EPickupTypes, float> PickupWeights;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Powerups")
	TMap<EPickupTypes, TSubclassOf<UPowerup>> PowerupClasses;
	

	//player related stuff
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	float PlayerMaxHealth = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	float ShieldMaxHealth = 50;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	float PlayerScoreMultiplier = 0.003;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	TArray<EShapeType> ShapeLoadout;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	TMap<EShapeType, UStaticMesh*> ShapeMeshTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced, Category = "Player")
	TMap<EShapeType, UAbility*> ShapeAbilityTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shapes")
	TMap<EShapeType, FShapeAbilityData> ShapeAbilityTexts;
	
	UFUNCTION(BlueprintCallable)
	void ShiftPlayer(AShifterCharacter* Player, EShapeType ToShape);
	UFUNCTION(BlueprintCallable)
	void CreateAndAssignPowerup(EPickupTypes Powerup);
	UFUNCTION()
	void NotifyPowerupExpired(UPowerup* Powerup);

	UPROPERTY()
	AShifterCharacter* GameCharacterPtr;

	UPROPERTY(BlueprintReadOnly)
	TArray<UPowerup*> ActivePowerups;

	UFUNCTION(BlueprintCallable)
	void EquipShape(EShapeType Type);
	
	UFUNCTION(BlueprintCallable)
	void UnequipShape(EShapeType Type);

	UFUNCTION(BlueprintCallable)
	void PauseAtCheckpoint(bool bPause);


	UFUNCTION(BlueprintCallable)
	float GetPlatformSpeed();

	UFUNCTION(BlueprintCallable)
	void SetPlatformSpeed(float Speed);

	
protected:
	
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Platform")
	float PlatformMovementSpeed;

	UPROPERTY(BlueprintReadOnly)
	bool bCheckpointPaused;

	//game related stuff.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Game")
	TArray<EShapeType> UnlockedShapes;

	
	
};
