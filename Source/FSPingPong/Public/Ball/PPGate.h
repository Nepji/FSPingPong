// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPBaseGameState.h"
#include "GameFramework/Actor.h"
#include "PPGate.generated.h"

class APPBall;
class UBoxComponent;

UCLASS()
class FSPINGPONG_API APPGate : public AActor
{
	GENERATED_BODY()

public:
	APPGate();

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Components")
	UBoxComponent* CollisionComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Game")
	ETeam Team;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Game")
	TSubclassOf<APPBall> BallClass;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
