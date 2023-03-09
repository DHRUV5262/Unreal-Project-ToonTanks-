// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class TOONTANKS_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	void HandleDestruction();

protected:
	void GetRotation(FVector ToTarget);
	void Fire();


private:
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Components" , meta = ( AllowPrivateAccess = "true"))
	class UCapsuleComponent* Capsule ;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Components" , meta = ( AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh ;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Components" , meta = ( AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Components" , meta = ( AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly , Category = "Combat")
	TSubclassOf<class AProjectiles> ProjectileClass;

	UPROPERTY(EditAnywhere)
	UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound ;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
