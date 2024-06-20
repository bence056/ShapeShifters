// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class APlatform;
class AShifterCharacter;


UENUM()
enum class EPickupTypes : uint8
{
	None,
	Health,
	Clockwork,
	Xray,
	TripleXP,
	Wireframe,
	Analyze,
	ExtraLife,
	Fly
};

UCLASS()
class SHAPESHIFTERS_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* RootComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bImmediateEffect;
	
	
	UPROPERTY()
	APlatform* OwningPlatform;

	UPROPERTY()
	int32 PosX;
	UPROPERTY()
	int32 PosY;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPickupTypes PickupType;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void ActivateImmediateEffect(AShifterCharacter* Character);
	
	UFUNCTION(BlueprintCallable)
	void OnPickupTriggered(AShifterCharacter* Character);

};
