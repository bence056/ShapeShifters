// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShapeSelectEntry.generated.h"

enum class EShapeType : uint8;
/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API UShapeSelectEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn))
	EShapeType AssignedType;
	
};
