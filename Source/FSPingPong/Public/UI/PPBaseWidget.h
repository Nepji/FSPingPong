// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class FSPINGPONG_API UPPBaseWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Show();
protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Animation;
};
