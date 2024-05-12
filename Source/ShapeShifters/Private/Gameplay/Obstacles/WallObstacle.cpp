﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Obstacles/WallObstacle.h"


// Sets default values
AWallObstacle::AWallObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWallObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

