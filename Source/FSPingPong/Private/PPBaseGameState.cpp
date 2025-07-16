// Fill out your copyright notice in the Description page of Project Settings.


#include "PPBaseGameState.h"

#include "Net/UnrealNetwork.h"

APPBaseGameState::APPBaseGameState()
{
	TeamBlueScore = 0;
	TeamRedScore = 0;

	bReplicates = true;
}

void APPBaseGameState::SetMatchState(EPPMatchState State)
{
	if (this == nullptr)
	{
		return;
	}
	if(State == MatchState)
	{
		return;
	}
	MatchState = State;
}

void APPBaseGameState::AddScore(ETeam Team)
{
	if (!HasAuthority())
	{
		return;
	}

	if (Team == ETeam::T_Blue)
	{
		TeamBlueScore++;
	}
	else if (Team == ETeam::T_Red)
	{
		TeamRedScore++;
	}
}

int32 APPBaseGameState::GetScore(ETeam Team) const
{
	if (Team == ETeam::T_Blue)
	{
		return TeamBlueScore;
	}
	else if (Team == ETeam::T_Red)
	{
		return TeamRedScore;
	}
	return 0;
}

void APPBaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APPBaseGameState, TeamBlueScore);
	DOREPLIFETIME(APPBaseGameState, TeamRedScore);
	DOREPLIFETIME(APPBaseGameState, MatchState);
}


void APPBaseGameState::OnRep_MatchState()
{
	OnMatchStateChanged.Broadcast(MatchState);
}
