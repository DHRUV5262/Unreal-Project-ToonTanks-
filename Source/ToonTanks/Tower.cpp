// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::BeginPlay()
{
	Super::BeginPlay();
    Tank =Cast<ATank>(UGameplayStatics::GetPlayerPawn(this ,0));

    GetWorldTimerManager().SetTimer(FireRateHandle , this , &ATower::CheckForFire , FireRate , true);

}
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(Tank){
        if(InFireRange()){
            GetRotation(Tank->GetActorLocation());
        }
    }
}

void ATower::CheckForFire(){
    if(Tank == nullptr){return;}
    if(InFireRange() && Tank->TankAlive ){
        Fire();
    }
}

bool ATower::InFireRange(){
    float dis = FVector::Dist(GetActorLocation()  , Tank->GetActorLocation());
       if(dis <= Distance){
            return true;  
        }
        else{
            return false;
        }
}

void ATower::HandleDestruction(){

    Super::HandleDestruction();
    Destroy();

}