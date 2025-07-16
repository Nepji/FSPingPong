#include "Ball/PPGate.h"

#include "PPBaseGameMode.h"
#include "Components/BoxComponent.h"


APPGate::APPGate()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetupAttachment(GetRootComponent());
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void APPGate::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}
	APPBaseGameMode* GameMode = Cast<APPBaseGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}
	GameMode->OnGoalScored(Team);
}
