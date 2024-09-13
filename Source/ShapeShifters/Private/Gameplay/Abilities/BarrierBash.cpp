// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/BarrierBash.h"

#include "Gameplay/Obstacles/BreakableObstacle.h"
#include "Gameplay/Player/ShifterCharacter.h"

void UBarrierBash::OnAbilityActivated(AShifterCharacter* PlayerCharacter)
{
	Super::OnAbilityActivated(PlayerCharacter);

	//destroy a barricade:

	FVector StartLoc = PlayerCharacter->GetActorLocation();
	FVector EndLoc = StartLoc + FVector::XAxisVector * 30000.f;
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(PlayerCharacter);

	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_Visibility, Params))
	{
		if(HitResult.GetActor() && HitResult.GetActor()->GetClass()->IsChildOf(ABreakableObstacle::StaticClass()))
		{
			//destroy the wall.
			if(ABreakableObstacle* BreakableObstacle = Cast<ABreakableObstacle>(HitResult.GetActor()))
			{
				BreakableObstacle->OnWallShot();
			}
				
		}
	}
	
}
