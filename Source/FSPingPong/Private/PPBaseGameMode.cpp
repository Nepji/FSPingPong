// Fill out your copyright notice in the Description page of Project Settings.


#include "PPBaseGameMode.h"

#include "Player/PPPlayerController.h"
#include "Player/PPPlayerPlatform.h"

APPBaseGameMode::APPBaseGameMode()
{
	DefaultPawnClass = APPPlayerPlatform::StaticClass();
	PlayerControllerClass = APPPlayerController::StaticClass();
	
}

void APPBaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}
