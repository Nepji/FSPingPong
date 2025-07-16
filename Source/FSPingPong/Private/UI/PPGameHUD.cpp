// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PPGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/PPBaseWidget.h"

void APPGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void APPGameHUD::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerHUDWidgetClass);
	check(SpectatorHUDWidgetClass);

	GameWidgets.Add(EPPMatchState::MS_InProgress, CreateWidget<UPPBaseWidget>(GetWorld(),PlayerHUDWidgetClass));
	GameWidgets.Add(EPPMatchState::MS_WaitingForPlayers, CreateWidget<UPPBaseWidget>(GetWorld(),SpectatorHUDWidgetClass));

	for(const TTuple<EPPMatchState,UPPBaseWidget*> GameWidgetPair : GameWidgets)
	{
		UPPBaseWidget* GameWidget = GameWidgetPair.Value;
		if(!GameWidget)
		{
			continue;
		}
		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (GetWorld())
	{
		if (APPBaseGameState* MyGameState = GetWorld()->GetGameState<APPBaseGameState>())
		{
			MyGameState->OnMatchStateChanged.AddDynamic(this, &ThisClass::OnMatchStateChanged);
		}
	}
}

void APPGameHUD::OnMatchStateChanged(const EPPMatchState State)
{
	if(CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if(GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}
}
