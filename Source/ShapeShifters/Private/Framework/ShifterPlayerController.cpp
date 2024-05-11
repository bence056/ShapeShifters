// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Framework/ShifterPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "ShapeShifters/Public/Gameplay/Player/GameCamera.h"
#include "ShapeShifters/Public/Gameplay/Player/ShifterCharacter.h"
#include "ShapeShifters/Public/Gameplay/World/ShifterSpawner.h"

void AShifterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AGameCamera::StaticClass());
	if(Actor)
	{
		if(AGameCamera* CameraActor = Cast<AGameCamera>(Actor))
		{
			Possess(CameraActor);

			if(ShifterClass)
			{
				if(AShifterSpawner* Locator = Cast<AShifterSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AShifterSpawner::StaticClass())))
				{
					int32 RandSpawnSlot = FMath::RandRange(0, Locator->GridWidth-1);
					ShifterCharacter = GetWorld()->SpawnActor<AShifterCharacter>(ShifterClass, Locator->GetGridLocationByIndex(RandSpawnSlot), Locator->GetActorRotation());
					ShifterCharacter->LaneIndex = RandSpawnSlot;
					CameraActor->SetControlledPlayer(ShifterCharacter);
				}
				
			}
			
		}
	}
	
}
