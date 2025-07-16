// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPBaseGameMode.h"
#include "GameFramework/HUD.h"
#include "PPGameHUD.generated.h"

class UPPBaseWidget;
/**
 * 
 */
UCLASS()
class FSPINGPONG_API APPGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> SpectatorHUDWidgetClass;

	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void OnMatchStateChanged(EPPMatchState State);
private:
	UPROPERTY()
	UPPBaseWidget* CurrentWidget = nullptr;

	UPROPERTY()
	TMap<TEnumAsByte<EPPMatchState>, UPPBaseWidget*> GameWidgets;
};
