// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Platform.generated.h"

class AObstacle;

UENUM()
enum class EPlatformContentTypes : uint8
{
	Wall,
	Breakable,
	Laser,
	Spike,
	Turret
};

USTRUCT(BlueprintType, Blueprintable)
struct FCellSpawnData
{
	GENERATED_BODY()

	FCellSpawnData();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 7, Delta = 1))
	int32 CellX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 7, Delta = 1))
	int32 CellY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRepeating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 7, Delta = 1, EditCondition = "bRepeating", EditConditionHides = true))
	int32 RepX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 7, Delta = 1, EditCondition = "bRepeating", EditConditionHides = true))
	int32 RepY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlatformContentTypes Type;
	
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FCellSpawnData> PlatformContent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	float Speed;
	virtual void FellOutOfWorld(const UDamageType& dmgType) override;

	UPROPERTY()
	TArray<FGridData> GridData;

	UFUNCTION(BlueprintCallable)
	FVector GetGridLocation(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable)
	void SpawnObstacle(EPlatformContentTypes Type, int32 X, int32 Y);
	TArray<FGridData*> GetEmptyInRow(int32 X);
	UFUNCTION()
	bool IsGridOccupiedAt(int32 X, int32 Y);
	UFUNCTION()
	void SetDataAt(int32 X, int32 Y, AObstacle* NewObstacle);
	
	TArray<FGridData*> GetCellsWithObstacle(TSubclassOf<AObstacle> ClassFilter);
	FGridData* GetCellDataAt(int32 X, int32 Y);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DestroyPlatformAndContents();
	UFUNCTION(BlueprintCallable)
	void GeneratePlatformContents();
	
};
