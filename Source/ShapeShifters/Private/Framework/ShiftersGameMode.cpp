// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeShifters/Public/Framework/ShiftersGameMode.h"

AShiftersGameMode::AShiftersGameMode()
{
	PlatformMovementSpeed = 100.f;
	MinimumWallGap = 2;
	MaxObstacleReplacementTrials = 3;
	MaxWallSpawnTrials = 3;
	MinimumWallWidth = 1;
	MaximumWallWidth = 8;
}
