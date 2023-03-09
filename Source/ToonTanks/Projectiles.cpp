// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectiles::AProjectiles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement -> MaxSpeed = 1300.f;
	ProjectileMovement -> InitialSpeed = 1300.f;

	TarilEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffext"));
	TarilEffect->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectiles::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this , &AProjectiles::OutHit );
	if(LaunchSound){
		UGameplayStatics::PlaySoundAtLocation(this , LaunchSound , GetActorLocation());	
	}
}

// Called every frame
void AProjectiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectiles::OutHit(UPrimitiveComponent *HitComp , AActor *OtherActor , UPrimitiveComponent *otherComp , FVector NormalImpulse , const FHitResult &Hit){
	
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) return ;

	auto Controller = GetOwner()->GetInstigatorController();
	auto DamageType = UDamageType::StaticClass();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner){
		UGameplayStatics::ApplyDamage(OtherActor, Damage , Controller , this , DamageType);
		if(HitEffect){
			UGameplayStatics::SpawnEmitterAtLocation(this , HitEffect , GetActorLocation() , GetActorRotation());
		}
		if(HitSound){
			UGameplayStatics::PlaySoundAtLocation(this , HitSound , GetActorLocation());	
		}
		if(HitCameraShakeClass){
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
		
	}
	Destroy();

}
