// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShifterCharacter.generated.h"

class UBoxComponent;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* ObstacleCollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector TargetLocation;

	virtual void PawnClientRestart() override;
	UFUNCTION()
	void HandleLaneMovement(const FInputActionInstance& Action);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PlayerHealth;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AShifterSpawner* GetSpawner();
	UFUNCTION(BlueprintCallable)
	void StepLeft();
	UFUNCTION(BlueprintCallable)
	void StepRight();
	UFUNCTION(BlueprintPure)
	float GetPlayerHealth();
	UFUNCTION(BlueprintPure)
	float GetPlayerHealthPercentage();
	UFUNCTION(BlueprintCallable)
	void SetPlayerHealth(float Health);
	UFUNCTION(BlueprintCallable)
	void ChangePlayerHealth(float DeltaHealth);
	
	
};
