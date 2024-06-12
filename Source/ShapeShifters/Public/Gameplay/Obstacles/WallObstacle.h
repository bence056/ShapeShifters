// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "WallObstacle.generated.h"

UCLASS()
class SHAPESHIFTERS_API AWallObstacle : public AObstacle
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWallObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPlayerCollided(AShifterCharacter* Player) override;
};
