// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShifterSpawner.generated.h"

class UBoxComponent;

UCLASS()
class SHAPESHIFTERS_API AShifterSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShifterSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* SpawnBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 GridWidth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	FVector GetGridLocationByIndex(int32 Index);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
