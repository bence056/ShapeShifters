// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShifterCharacter.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
