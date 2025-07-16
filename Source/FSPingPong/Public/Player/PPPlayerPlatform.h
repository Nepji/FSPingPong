// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PPPlayerPlatform.generated.h"

class UFloatingPawnMovement;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class FSPINGPONG_API APPPlayerPlatform : public APawn
{
	GENERATED_BODY()

public:
	APPPlayerPlatform();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Input")
	UInputAction* OneAxisMovement;
	
protected:
	virtual void BeginPlay() override;
	
private:

	void InputMove(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Server_MoveForward(const FVector& ReplicatedLocation);
	
};
