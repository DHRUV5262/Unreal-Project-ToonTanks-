// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"


UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	void ActorDied(AActor* Actor);

	void HandleGameStart();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool BWonGame);

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayReady();

	

private :

	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly)
	float StartTime = 3.f;

	class AToonTanksPlayerController* tPlayerController;

	int32 GetTargetCount();

	int32 TargetTowers ;

};
