
#include "Player/PPPlayerPlatform.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"


APPPlayerPlatform::APPPlayerPlatform()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	SetReplicateMovement(true);
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SetRootComponent(MeshComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	
}

void APPPlayerPlatform::BeginPlay()
{
	checkf(CameraComponent, TEXT("Camera Component Required"));
	checkf(MeshComponent, TEXT("Camera Component Required"));
	
	Super::BeginPlay();
}

void APPPlayerPlatform::InputMove(const FInputActionValue& Value)
{
	const float MovementVector = Value.Get<float>();
	if(!GetController() || MovementVector == 0)
	{
		return;
	}
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	FVector Loc = GetActorLocation();
	AddMovementInput(RightDirection, MovementVector);
	Server_MoveForward(GetActorLocation());
}


void APPPlayerPlatform::Server_MoveForward_Implementation(const FVector& ReplicatedLocation)
{
	SetActorLocation(ReplicatedLocation);
}
void APPPlayerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APPPlayerPlatform::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(OneAxisMovement, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
	}
}

