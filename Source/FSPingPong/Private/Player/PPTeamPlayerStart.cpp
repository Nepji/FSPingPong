// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PPTeamPlayerStart.h"

#include "Player/PPPlayerState.h"

class APPPlayerState;

bool APPTeamPlayerStart::IsSuitableForPlayer(APlayerController* PlayerController) const
{
	if (!PlayerController)
		return false;

	if (APPPlayerState* PS = PlayerController->GetPlayerState<APPPlayerState>())
	{
		return PS->GetTeam() == StartTeam; 
	}

	return false;
}


