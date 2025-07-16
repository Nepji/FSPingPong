// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/PPBallHUB.h"

#include "Ball/PPBall.h"

APPBallHUB::APPBallHUB()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPBallHUB::StartRound()
{	
	if (!GetWorld() || !HasAuthority())
	{
		return;
	}
	
	GetWorld()->GetTimerManager().SetTimer(StartDelayHande,this,&ThisClass::OnBallStart,StartDelay, false);
}

void APPBallHUB::RestartRound()
{
	if (!OwnedBall || !HasAuthority())
	{
		return;
	}
	OwnedBall->EndRound();
	OwnedBall->SetActorLocation(GetActorLocation());
	StartRound();
}

void APPBallHUB::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BallClass) && HasAuthority() && GetWorld())
	{
		const FTransform SpawnTransform(FRotator::ZeroRotator, GetActorLocation());
		AActor* SpawnedBall = GetWorld()->SpawnActor(BallClass, &SpawnTransform);
		OwnedBall = Cast<APPBall>(SpawnedBall);
	}
}

void APPBallHUB::OnBallStart()
{
	if (!OwnedBall)
	{
		return;
	}

	OwnedBall->BeginRound();
}



