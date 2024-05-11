// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCamera.generated.h"

class UCameraComponent;

UCLASS()
class SHAPESHIFTERS_API AGameCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameCamera();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* ViewCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
