// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PPPlayerState.h"

#include "Net/UnrealNetwork.h"

APPPlayerState::APPPlayerState(): Team(ETeam::T_Default)
{
	bReplicates = true;
}

void APPPlayerState::SetTeam(ETeam NewTeam)
{
	if (!HasAuthority())
	{
		return;
	}
	Team = NewTeam;
	OnRep_Team();
}

void APPPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APPPlayerState, Team);
}

void APPPlayerState::OnRep_Team()
{
	
}
