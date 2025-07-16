// Fill out your copyright notice in the Description page of Project Settings.


#include "PPBaseGameMode.h"

#include "EngineUtils.h"
#include "PPBaseGameState.h"
#include "Ball/PPBallHUB.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PPPlayerController.h"
#include "Player/PPPlayerPlatform.h"
#include "Player/PPPlayerState.h"
#include "Player/PPTeamPlayerStart.h"
#include "UI/PPGameHUD.h"

class APlayerStart;
class APPPlayerState;

APPBaseGameMode::APPBaseGameMode()
{
	DefaultPawnClass = APPPlayerPlatform::StaticClass();
	PlayerControllerClass = APPPlayerController::StaticClass();
	GameStateClass = APPBaseGameState::StaticClass();
	HUDClass = APPGameHUD::StaticClass();

	ReadyPlayers.Empty();
}

void APPBaseGameMode::CheckStartMatch()
{
	if (ReadyPlayers.Num() != PlayersNeeded || ReadyPlayers.Num() == 0)
	{
		if (BaseGameState)
		{
			BaseGameState->SetMatchState(MS_WaitingForPlayers);
		}
		return;		
	}
	StartMatch();
}

void APPBaseGameMode::OnGoalScored(ETeam Team) const
{
	if (!HasAuthority())
	{
		return;
	}
	if (APPBaseGameState* GS = GetGameState<APPBaseGameState>())
	{
		GS->AddScore(Team);
	}

	if (BallHub)
	{
		BallHub->RestartRound();
	}

}
void APPBaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	BaseGameState = Cast<APPBaseGameState>(GameState);
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APPBallHUB::StaticClass(), FoundActors);
	if (!FoundActors.IsEmpty())
	{
		BallHub = Cast<APPBallHUB>(FoundActors[0]);
	}
}


void APPBaseGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	if (APPPlayerState* PS = Cast<APPPlayerState>(NewPlayer->PlayerState))
	{
		if (GameState->PlayerArray.Num() == 1)
		{
			PS->SetTeam(ETeam::T_Red);
		}
		else
		{
			PS->SetTeam(ETeam::T_Blue);
		}
	}
	ReadyPlayers.AddUnique(NewPlayer);
	CheckStartMatch();
}

AActor* APPBaseGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (!Player)
	{
		return Super::ChoosePlayerStart_Implementation(Player);
	}
	APPPlayerState* PS = Player->GetPlayerState<APPPlayerState>();
	if (!PS)
	{
		return Super::ChoosePlayerStart_Implementation(Player);
	}
	
	TArray<APlayerStart*> PlayerStarts;
	for (TActorIterator<APPTeamPlayerStart> It(GetWorld()); It; ++It)
	{
		if (APPTeamPlayerStart* TeamStart = *It)
		{
			APlayerController* PC = Cast<APlayerController>(Player);
			if (PC && TeamStart->IsSuitableForPlayer(PC))
			{
				return TeamStart;
			}
		}
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}

void APPBaseGameMode::StartMatch()
{
	if (BaseGameState)
	{
		BaseGameState->SetMatchState(EPPMatchState::MS_InProgress);
	}
	if (BallHub)
	{
		BallHub->StartRound();
	}
}
