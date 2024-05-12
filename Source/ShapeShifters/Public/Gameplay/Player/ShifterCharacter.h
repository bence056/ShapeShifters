// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShifterCharacter.generated.h"

class AShifterSpawner;
struct FInputActionInstance;
class UInputMappingContext;
class UCameraComponent;
class UInputAction;
class AGameCamera;

UCLASS()
class SHAPESHIFTERS_API AShifterCharacter : public APawn
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* ViewCamera;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Actions")
	UInputAction* LaneChangeInputLeft;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Actions")
	UInputAction* LaneChangeInputRight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector TargetLocation;

	virtual void PawnClientRestart() override;
	UFUNCTION()
	void HandleLaneMovement(const FInputActionInstance& Action);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AShifterSpawner* GetSpawner();
	UFUNCTION(BlueprintCallable)
	void StepLeft();
	UFUNCTION(BlueprintCallable)
	void StepRight();
	
};
