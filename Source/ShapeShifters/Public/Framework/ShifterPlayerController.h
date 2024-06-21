// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShifterPlayerController.generated.h"

class UCheckpointWidget;
class UPlayerHud;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PlayerHudClass;
	UPROPERTY(BlueprintReadOnly)
	UPlayerHud* PlayerHud;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PauseWidgetClass;
	UPROPERTY(BlueprintReadWrite)
	UCheckpointWidget* PauseWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PlayerDeathUIClass;
	
	UFUNCTION(BlueprintCallable)
	void TogglePlayerHud(bool bOn);
	UFUNCTION()
	void TriggerPlayerDeath();
	UFUNCTION()
	void TriggerPlayerRebirth();

	UFUNCTION(BlueprintCallable)
	void CreateHealthPopup(float Health);
	UFUNCTION()
	void UpdatePowerupsVisual();
	UFUNCTION(BlueprintCallable)
	void TriggerCheckpointPaused(bool bPaused);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HealthPopupWidget;

protected:


	UPROPERTY(BlueprintReadOnly)
	AShifterCharacter* ShifterCharacter;
	
	virtual void BeginPlay() override;
	
};
