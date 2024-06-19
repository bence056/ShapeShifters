// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformKiller.generated.h"

class APlatform;
class UBoxComponent;

UCLASS()
class SHAPESHIFTERS_API APlatformKiller : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatformKiller();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* KillArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> KillClasses;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
