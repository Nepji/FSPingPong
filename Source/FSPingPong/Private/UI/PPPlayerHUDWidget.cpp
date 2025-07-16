// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PPPlayerHUDWidget.h"

#include "PPBaseGameMode.h"

bool UPPPlayerHUDWidget::GetMatchStatistic(FText& BlueStatistic, FText& RedStatistic) const
{
	if (!GetWorld())
	{
		return false;
	}
	APPBaseGameState* GameState = Cast<APPBaseGameState>(GetWorld()->GetGameState());
	if (!GameState)
	{
		return false;
	}
	BlueStatistic = FText::AsNumber(GameState->GetScore(ETeam::T_Blue));
	RedStatistic = FText::AsNumber(GameState->GetScore(ETeam::T_Red));
	return true;
}
