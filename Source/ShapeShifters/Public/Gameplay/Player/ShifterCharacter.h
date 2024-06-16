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

UENUM(Blueprintable, BlueprintType)
enum class EShapeType : uint8
{
	Cube,
	Ball,
	Cylinder,
	Pyramid,
	Octahedron,
	Dodecahedron,
	MobiusStrip
};

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LaneSwapSpeed = 8.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LaneSwapSpeedAsBall = 14.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector TargetLocation;
	UPROPERTY()
	bool bCanMove;

	virtual void PawnClientRestart() override;
	UFUNCTION()
	void HandleLaneMovement(const FInputActionInstance& Action);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PlayerHealth;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadOnly)
	float CurrentScore = 0;

	UPROPERTY(BlueprintReadWrite)
	EShapeType CurrentShapeType;
	
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
	UFUNCTION()
	void ToggleSideMovement(bool bOn);

	UFUNCTION(BlueprintPure)
	EShapeType GetShapeType();
	UFUNCTION(BlueprintCallable)
	void SetShapeType(EShapeType ToSet);
	UFUNCTION()
	void OnPlayerShifted(EShapeType Shape);
};
