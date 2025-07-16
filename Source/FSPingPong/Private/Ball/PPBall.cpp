#include "Ball/PPBall.h"


void APPBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	//
}

void APPBall::BeginRound() const
{
	if (HasAuthority())
	{
		MeshComponent->AddImpulse(FMath::VRand().GetSafeNormal() * Velocity, FName(), true);
	}
}

void APPBall::EndRound() const
{
	if (HasAuthority())
	{
		MeshComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
		MeshComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}
}

APPBall::APPBall()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetConstraintMode(EDOFMode::XYPlane);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	MeshComponent->SetIsReplicated(true);
	
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);

	MeshComponent->OnComponentHit.AddDynamic(this, &APPBall::OnHit);

	Velocity = InitSpeed;
}

void APPBall::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		MeshComponent->SetSimulatePhysics(false);
	}
}

void APPBall::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HasAuthority())
	{
		return;
	}
	Velocity = FMath::Clamp(Velocity + BonusSpeedThreshold, 0 , MaxSpeed);
	const FVector NewVelocity = MeshComponent->GetPhysicsLinearVelocity().GetSafeNormal() * Velocity;
	MeshComponent->SetPhysicsLinearVelocity(NewVelocity);
	
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}

