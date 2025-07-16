// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPBaseGameState.h"
#include "GameFramework/PlayerStart.h"
#include "PPTeamPlayerStart.generated.h"

UCLASS()
class FSPINGPONG_API APPTeamPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	bool IsSuitableForPlayer(APlayerController* PlayerController) const;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spawn")
	ETeam StartTeam;

};
