// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectiles.generated.h"

UCLASS()
class TOONTANKS_API AProjectiles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectiles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly , Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement ;

	UFUNCTION()
	void OutHit(UPrimitiveComponent *HitComp , AActor *OtherActor , UPrimitiveComponent *otherComp , FVector NormalImpulse , const FHitResult &Hit);

	UPROPERTY(EditAnywhere , Category = "Combat")
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitEffect ;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystemComponent* TarilEffect;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound ;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* HitSound ;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;


};
