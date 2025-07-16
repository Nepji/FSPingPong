#include "Player/PPPlayerController.h"
#include "EnhancedInputSubsystems.h"

void APPPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		   ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	if (GetWorld())
	{
		if (APPBaseGameState* MyGameState = GetWorld()->GetGameState<APPBaseGameState>())
		{
			MyGameState->OnMatchStateChanged.AddDynamic(this, &ThisClass::OnMatchStateChanged);
		}
	}
}

void APPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void APPPlayerController::OnMatchStateChanged(EPPMatchState State)
{
	if (State == EPPMatchState::MS_InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}
