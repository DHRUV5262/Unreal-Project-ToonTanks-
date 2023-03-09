// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetOwner()->OnTakeAnyDamage.AddDynamic(this , &UHealthComponent::DamageTaken);
	GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this , 0));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor *DamagedActor , float Damage , const UDamageType *DamageType , AController *Instigator , AActor *DamageCauser){

	if(Tank){
		if(DamagedActor == Tank){
			if(Damage < 0.f) return;
				TankHealth = TankHealth - Damage ;
			if(TankHealth <= 0.f){
				GameMode->ActorDied(DamagedActor);
			}
		}
		else{
			if(Damage < 0.f) return;
				TowerHealth = TowerHealth - Damage ;
			if(TowerHealth <= 0.f){
				GameMode->ActorDied(DamagedActor);
			}
		}
	}
	

}
	

