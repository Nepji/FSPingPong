// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPBaseWidget.h"
#include "PPPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class FSPINGPONG_API UPPPlayerHUDWidget : public UPPBaseWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetMatchStatistic(FText& BlueStatistic, FText& RedStatistic) const;
	

	
};
