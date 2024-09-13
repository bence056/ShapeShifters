// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "BreakableObstacle.generated.h"

UCLASS()
class SHAPESHIFTERS_API ABreakableObstacle : public AObstacle
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABreakableObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWallShot_Internal();
	
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnWallShot();
};
