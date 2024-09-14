// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShiftersMenuController.generated.h"

/**
 * 
 */
UCLASS()
class SHAPESHIFTERS_API AShiftersMenuController : public APlayerController
{
	GENERATED_BODY()

public:

	AShiftersMenuController();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* MenuWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAudioComponent* MenuMusicComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TObjectPtr<USoundBase>> MainMenuMusicSet;
	

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void PlayMenuMusicLoop();
	
};
