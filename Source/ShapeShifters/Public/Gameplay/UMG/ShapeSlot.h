// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShapeSlot.generated.h"

class UCheckBox;
enum class EShapeType : uint8;
/**
 * 
 */

USTRUCT(Blueprintable, BlueprintType)
struct FShapeAbilityData
{
	GENERATED_BODY()

public:

	FShapeAbilityData();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShapeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShapeAbilityDesc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShapePassiveDesc;
	
	
};

UCLASS()
class SHAPESHIFTERS_API UShapeSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn))
	int32 ShapeIndex;
	
};
