// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShifterPlayerController.generated.h"

class AShifterCharacter;
/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API AShifterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AShifterCharacter> ShifterClass;

protected:


	UPROPERTY(BlueprintReadOnly)
	AShifterCharacter* ShifterCharacter;
	
	virtual void BeginPlay() override;
	
};
