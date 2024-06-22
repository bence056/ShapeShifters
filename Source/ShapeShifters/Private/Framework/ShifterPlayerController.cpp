// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Framework/ShifterPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Framework/ShifterGameInstance.h"
#include "Framework/ShiftersGameMode.h"
#include "Gameplay/UMG/CheckpointWidget.h"
#include "Gameplay/UMG/HealthPopup.h"
#include "Gameplay/UMG/NotificationPopup.h"
#include "Gameplay/UMG/PlayerHud.h"
#include "Kismet/GameplayStatics.h"
#include "ShapeShifters/Public/Gameplay/Player/ShifterCharacter.h"
#include "ShapeShifters/Public/Gameplay/World/ShifterSpawner.h"

class UHealthPopup;

void AShifterPlayerController::TogglePlayerHud(bool bOn)
{
	if(!PlayerHud && PlayerHudClass) PlayerHud = CreateWidget<UPlayerHud>(this, PlayerHudClass);
	if(PlayerHud)
	{
		if(bOn)
		{
			PlayerHud->AddToViewport();
		}else
		{
			PlayerHud->RemoveFromParent();
		}
	}
}

void AShifterPlayerController::TriggerPlayerDeath()
{
	if(PlayerDeathUIClass) CreateWidget(this, PlayerDeathUIClass)->AddToViewport();
	if(AShiftersGameMode* GameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		//stop the platforms.
		GameMode->SetPlatformSpeed(0.f);
		GameMode->PlatformAcceleration = 0.f;
		
	}
	if(AShifterCharacter* SCharacter = Cast<AShifterCharacter>(GetPawn()))
	{
		if(UShifterGameInstance* ShifterGameInstance = Cast<UShifterGameInstance>(GetGameInstance()))
		{
			SCharacter->ToggleSideMovement(false);
			if(SCharacter->CurrentScore > ShifterGameInstance->HighScore)
			{
				ShifterGameInstance->HighScore = SCharacter->CurrentScore;
			}
		}
		
	}
}

void AShifterPlayerController::TriggerPlayerRebirth()
{
	if(ShifterClass)
	{
		if(AShifterSpawner* Locator = Cast<AShifterSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AShifterSpawner::StaticClass())))
		{
			int32 RandSpawnSlot = FMath::RandRange(0, Locator->GridWidth-1);
			ShifterCharacter = GetWorld()->SpawnActor<AShifterCharacter>(ShifterClass, Locator->GetGridLocationByIndex(RandSpawnSlot), Locator->GetActorRotation());
			ShifterCharacter->LaneIndex = RandSpawnSlot;
			Possess(ShifterCharacter);
			SetShowMouseCursor(true);
			if(AShiftersGameMode* GameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
			{
				GameMode->GameCharacterPtr = ShifterCharacter;
				GameMode->PauseAtCheckpoint(true);
			}
		}
				
	}
}

void AShifterPlayerController::CreateHealthPopup(float Health)
{
	UHealthPopup* HealthPopup = CreateWidget<UHealthPopup>(this, HealthPopupWidget);
	HealthPopup->DeltaHealth = Health;
	HealthPopup->AddToViewport();
	HealthPopup->TriggerPopup();
}

void AShifterPlayerController::CreateNotificationPopup(const FText& NotificationText)
{
	UNotificationPopup* NotificationPopup = CreateWidget<UNotificationPopup>(this, NotificationPopupWidget);
	NotificationPopup->MessageText = NotificationText;
	NotificationPopup->AddToViewport();
	NotificationPopup->TriggerPopup();
}

void AShifterPlayerController::UpdatePowerupsVisual()
{
	if(AShiftersGameMode* ShiftersGameMode = Cast<AShiftersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		//do the ui shit.
		if(PlayerHud)
		{
			PlayerHud->UpdatePowerupsUI();
		}
	}
}

void AShifterPlayerController::TriggerCheckpointPaused(bool bPaused)
{
	if(PauseWidgetClass && !PauseWidget)
	{
		PauseWidget = CreateWidget<UCheckpointWidget>(this, PauseWidgetClass);
	}
	if(bPaused)
	{
		TogglePlayerHud(false);
		PauseWidget->AddToViewport();
	}
	else
	{
		PauseWidget->RemoveFromParent();
		TogglePlayerHud(true);
	}
}

void AShifterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerPlayerRebirth();
}
