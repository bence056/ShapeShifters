﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/World/Platform.h"
#include "Obstacle.generated.h"

class AShifterCharacter;
class APlatform;

UCLASS()
class SHAPESHIFTERS_API AObstacle : public AActor
{
	GENERATED_BODY()

	friend class APlatform;
	
public:
	// Sets default values for this actor's properties
	AObstacle();

	UPROPERTY()
	int32 PosX;
	UPROPERTY()
	int32 PosY;
	UPROPERTY(EditDefaultsOnly)
	float DamageToDeal;

	UPROPERTY()
	EPlatformContentTypes ObstacleType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	APlatform* OwningPlatform;

	UFUNCTION()
	FORCEINLINE FVector GetRelativeLocation() {return OwningPlatform->GetActorLocation() - GetActorLocation();}

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerDamageTaken();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnPlayerCollided(AShifterCharacter* Player);
};
