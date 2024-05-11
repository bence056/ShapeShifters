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
					for(int32 i=0; i<8; i++)
					{
						UE_LOG(LogTemp, Warning, TEXT("%s"), *Locator->GetGridLocationByIndex(i).ToString());
						GetWorld()->SpawnActor<AShifterCharacter>(ShifterClass, Locator->GetGridLocationByIndex(i), Locator->GetActorRotation());
					}
					// ShifterCharacter = GetWorld()->SpawnActor<AShifterCharacter>(ShifterClass, Locator->GetActorLocation(), Locator->GetActorRotation());
				}
				
			}
			
		}
	}
	
}
