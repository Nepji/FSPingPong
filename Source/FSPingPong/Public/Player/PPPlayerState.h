// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPBaseGameState.h"
#include "GameFramework/PlayerState.h"
#include "PPPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FSPINGPONG_API APPPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Team")
	FORCEINLINE ETeam GetTeam() const { return Team; }
public:
	APPPlayerState();

	void SetTeam(ETeam NewTeam);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Team, BlueprintReadOnly, Category = "Team")
	ETeam Team;

	UFUNCTION()
	void OnRep_Team();
};
