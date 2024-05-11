// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShifterCharacter.generated.h"

class AGameCamera;

UCLASS()
class SHAPESHIFTERS_API AShifterCharacter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShifterCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* RootComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* ShapeMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 LaneIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	AGameCamera* ControllingCamera;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void SetCameraActor(AGameCamera* Cam);
	
	UFUNCTION(BlueprintCallable)
	void StepLeft();
	UFUNCTION(BlueprintCallable)
	void StepRight();
	
};
