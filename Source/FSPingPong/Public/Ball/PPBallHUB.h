// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPBallHUB.generated.h"

class APPBall;

UCLASS()
class FSPINGPONG_API APPBallHUB : public AActor
{
	GENERATED_BODY()

public:
	APPBallHUB();
	
	void StartRound();
	void RestartRound();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category ="Ball")
	TSubclassOf<APPBall> BallClass;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Time")
	float StartDelay =4.f; 
private:
	TSoftObjectPtr<APPBall> OwnedBall;
	FTimerHandle StartDelayHande;
private:
	void OnBallStart();
};
