﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

class AObstacle;
enum class EPlatformContentTypes : uint8;
class UBoxComponent;
class APlatform;

UCLASS()
class SHAPESHIFTERS_API APlatformSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatformSpawner();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<TSubclassOf<APlatform>, float> PlatformClasses;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* SpawnArea;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxPlatformCount = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bFreeplaySpawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "!bFreeplaySpawn", EditConditionHides = true))
	int32 FixPlaySeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "!bFreeplaySpawn", EditConditionHides = true))
	int32 LevelLength;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<APlatform*> PlatformsInArea;

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	int32 CurrentLevelLength;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
