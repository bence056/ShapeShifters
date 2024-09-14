// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ShiftersMenuController.h"

#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"


AShiftersMenuController::AShiftersMenuController()
{
	MenuMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MenuMusic"));
	MenuMusicComponent->SetAutoActivate(false);
}

void AShiftersMenuController::BeginPlay()
{
	Super::BeginPlay();

	if(MenuWidgetClass)
	{
		MenuWidget = CreateWidget(this, MenuWidgetClass);
		MenuWidget->AddToViewport();
		SetShowMouseCursor(true);
	}
	
	MenuMusicComponent->OnAudioFinished.AddDynamic(this, &AShiftersMenuController::PlayMenuMusicLoop);
	PlayMenuMusicLoop();
	
}

void AShiftersMenuController::PlayMenuMusicLoop()
{
	if(MainMenuMusicSet.Num() > 0)
	{
		int32 RandIndex = FMath::RandRange(0, MainMenuMusicSet.Num()-1);
		MenuMusicComponent->SetSound(MainMenuMusicSet[RandIndex].Get());
		MenuMusicComponent->Activate(true);
	}
}
