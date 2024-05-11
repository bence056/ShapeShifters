// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputMappingContext.h"
#include "GameCamera.generated.h"

class AShifterSpawner;
class AShifterCharacter;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Actions")
	UInputAction* LaneChangeInputLeft;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input | Actions")
	UInputAction* LaneChangeInputRight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY()
	AShifterCharacter* ControlledPlayer;
	
	virtual void PawnClientRestart() override;
	UFUNCTION()
	void HandleLaneMovement(const FInputActionInstance& Action);
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void SetControlledPlayer(AShifterCharacter* Player);

	UFUNCTION(BlueprintCallable)
	AShifterSpawner* GetSpawner();
	
};
