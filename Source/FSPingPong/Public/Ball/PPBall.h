#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPBall.generated.h"

class USphereComponent;

UCLASS()
class FSPINGPONG_API APPBall : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void BeginRound() const;
	void EndRound() const;
	APPBall();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Speed")
	float BonusSpeedThreshold = 30.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Speed")
	float InitSpeed = 250.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Speed")
	float MaxSpeed = 30.f;
	

protected:
	virtual void BeginPlay() override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	float Velocity = 0;
};
