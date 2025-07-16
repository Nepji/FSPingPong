// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PPBaseGameState.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	T_Default,
	T_Blue		UMETA(DisplayName = "Team Blue"),
	T_Red		UMETA(DisplayName = "Team Red")
};

UENUM()
enum EPPMatchState
{
	MS_Default,
	MS_WaitingForPlayers,
	MS_InProgress
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchStateChanged,EPPMatchState, NewState);

UCLASS()
class FSPINGPONG_API APPBaseGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	FOnMatchStateChanged OnMatchStateChanged;
public:
	APPBaseGameState();
	void SetMatchState(EPPMatchState State);
	
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(ETeam Team);

	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetScore(ETeam Team) const;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	UPROPERTY(Replicated)
	int32 TeamBlueScore;
	
	UPROPERTY(Replicated)
	int32 TeamRedScore;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	TEnumAsByte<EPPMatchState> MatchState;

private:
	UFUNCTION()
	void OnRep_MatchState();
};
