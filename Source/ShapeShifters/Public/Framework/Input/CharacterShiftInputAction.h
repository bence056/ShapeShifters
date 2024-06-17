// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "CharacterShiftInputAction.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SHAPESHIFTERS_API UCharacterShiftInputAction : public UInputAction
{
	GENERATED_BODY()

public:

	UCharacterShiftInputAction();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ShapeIndex;
	
};
