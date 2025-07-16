// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPBaseGameState.h"
#include "GameFramework/GameModeBase.h"
#include "PPBaseGameMode.generated.h"

class APPBallHUB;

UCLASS()
class FSPINGPONG_API APPBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, Category ="HUB")
	TSoftObjectPtr<APPBallHUB> BallHub;
public:
	APPBaseGameMode();
	void CheckStartMatch();
	void OnGoalScored(ETeam Team) const;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
	int32 PlayersNeeded = 2;
protected:
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
private:
	void StartMatch();
private:
	TArray<TSoftObjectPtr<APlayerController>> ReadyPlayers;
	TSoftObjectPtr<APPBaseGameState> BaseGameState;

	
};

