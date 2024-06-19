// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class APlatform;
class AShifterCharacter;


UENUM()
enum class EPickupTypes
{
	None,
	Health,
	Clockwork,
	Xray,
	TripleXP,
	Wireframe,
	Analyze,
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

	UPROPERTY()
	APlatform* OwningPlatform;

	UPROPERTY()
	int32 PosX;
	UPROPERTY()
	int32 PosY;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(BlueprintReadOnly)
	EPickupTypes PickupType;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnPickupTriggered(AShifterCharacter* Character);

};
