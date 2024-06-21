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
UCLASS()
class SHAPESHIFTERS_API UShapeSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn))
	EShapeType AssignedType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* CheckBoxWidget;
	
};
