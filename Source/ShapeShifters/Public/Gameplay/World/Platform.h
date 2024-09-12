// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Platform.generated.h"

enum class EPickupTypes : uint8;
class APickup;
class AObstacle;

UENUM()
enum class EPlatformContentTypes : uint8
{
	None,
	Wall,
	Breakable,
	Laser,
	Spike,
	Turret
};

USTRUCT(Blueprintable, BlueprintType)
  struct FGridData
  {
  	GENERATED_BODY()
  
  	FGridData();
  
  	UPROPERTY()
  	int32 CellX;
  	UPROPERTY()
  	int32 CellY;
  	UPROPERTY()
  	AObstacle* ContainedObstacle;
  	UPROPERTY()
  	EPlatformContentTypes ObstacleType;
  	
  	
  };

USTRUCT(Blueprintable, BlueprintType)
struct FPickupData
{
	GENERATED_BODY()

	FPickupData();

	UPROPERTY()
	int32 CellX;
	UPROPERTY()
	int32 CellY;
	UPROPERTY()
	APickup* ContainedPickup;
	UPROPERTY()
	EPickupTypes PickupType;
	
	
};

UCLASS()
class SHAPESHIFTERS_API APlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatform();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* PlatformMesh;
	UPROPERTY()
	APlatform* LinkedPlatform;

	UPROPERTY()
	TArray<int32> BlockedRows;
	UPROPERTY()
	TArray<int32> PreReservedRows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInterface* ScoreBasedMat;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void FellOutOfWorld(const UDamageType& dmgType) override;

	UPROPERTY()
	TArray<FGridData> GridData;

	UPROPERTY()
	TArray<FPickupData> PickupGridData;

	UFUNCTION(BlueprintCallable)
	FVector GetGridLocation(int32 X, int32 Y);
public:
	UFUNCTION(BlueprintCallable)
	void SpawnObstacle(EPlatformContentTypes Type, int32 X, int32 Y);
	UFUNCTION(BlueprintCallable)
	void SpawnPickup(EPickupTypes Type, int32 X, int32 Y);
	TArray<FGridData*> GetEmptyInRow(int32 X);
	UFUNCTION()
	bool IsGridOccupiedAt(int32 X, int32 Y);
	UFUNCTION()
	void SetDataAt(int32 X, int32 Y, AObstacle* NewObstacle, EPlatformContentTypes Type);
	UFUNCTION()
	void SetPickupDataAt(int32 X, int32 Y, APickup* NewPickup, EPickupTypes Type);
	
	TArray<FGridData*> GetCellsWithObstacle(EPlatformContentTypes Type);
	FGridData* GetCellDataAt(int32 X, int32 Y);
	FPickupData* GetPickupDataAt(int32 X, int32 Y);


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bUseGlobalSeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "!bUseGlobalSeed", EditConditionHides = true))
	bool bUseCustomSeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bUseCustomSeed", EditConditionHides = true))
	int32 CustomSeed;

	UFUNCTION()
	void SetWallBlocks(int32 NewWallRow);
	
	TArray<FGridData*> GetAllowedWallReplacements(EPlatformContentTypes Type);

	TArray<TPair<int32, int32>> GetEmptyCells();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DestroyPlatformAndContents();
	UFUNCTION(BlueprintCallable)
	void GeneratePlatformContents();
	
};
