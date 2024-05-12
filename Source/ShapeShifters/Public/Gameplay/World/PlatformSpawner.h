// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

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
	TSubclassOf<APlatform> PlatformClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* SpawnArea;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxPlatformCount = 10;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<APlatform*> PlatformsInArea;

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
