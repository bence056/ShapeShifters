// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShapeSelector.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSelectorClicked);

UCLASS()
class SHAPESHIFTERS_API UShapeSelector : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, BlueprintAssignable)
	FSelectorClicked OnSelectorClicked;
	
};
