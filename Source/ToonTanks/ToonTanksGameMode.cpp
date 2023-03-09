// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "Engine/EngineTypes.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor *DeadActor){

    if(DeadActor == Tank){
        Tank->HandleDestruction();
        if(tPlayerController){
          tPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)){
        DestroyedTower->HandleDestruction();
       
        TargetTowers --;
        if(TargetTowers == 0){
            GameOver(true);
        }
    }

}

void AToonTanksGameMode::HandleGameStart(){

    if(GetWorld()->GetName() == "Main")
    {
        TargetTowers = GetTargetCount();
        Tank= Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
        tPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this , 0));
        StartGame();
        if(tPlayerController){
            tPlayerController->SetPlayerEnabledState(false);
            FTimerHandle PlayerEnabledTimeHandler ;
            FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
                tPlayerController,
                &AToonTanksPlayerController::SetPlayerEnabledState,
                true
                );
            GetWorldTimerManager().SetTimer(PlayerEnabledTimeHandler , PlayerEnabledTimerDelegate , StartTime , false);
            }
    }

}
int32 AToonTanksGameMode::GetTargetCount(){

    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this , ATower::StaticClass() , Towers);
    return Towers.Num();
}   

