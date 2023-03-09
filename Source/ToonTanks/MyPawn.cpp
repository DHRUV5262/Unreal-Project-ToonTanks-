// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule ;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankBase"));
	BaseMesh->SetupAttachment(Capsule);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankTurret"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("PrjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void AMyPawn::GetRotation(FVector ToTarget){

	FVector Target = ToTarget - TurretMesh->GetComponentLocation();
	FRotator Rotate = FRotator(0.0f,Target.Rotation().Yaw,0.0f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation() ,
		Rotate , 
		UGameplayStatics::GetWorldDeltaSeconds(this) ,
		 5.0f ));
}

void AMyPawn::Fire(){

	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	
	auto Projectile = GetWorld()->SpawnActor<AProjectiles>(ProjectileClass , Location , Rotation);
	Projectile->SetOwner(this);
}

void AMyPawn::HandleDestruction(){

	if(DeathEffect){
		UGameplayStatics::SpawnEmitterAtLocation(this , DeathEffect , GetActorLocation() , GetActorRotation());
		
	}
	if(DeathSound){
		UGameplayStatics::PlaySoundAtLocation(this , DeathSound , GetActorLocation() );
	}

	if(DeathCameraShakeClass){
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}