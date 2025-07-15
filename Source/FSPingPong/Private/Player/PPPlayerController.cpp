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
}

void APPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void APPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
