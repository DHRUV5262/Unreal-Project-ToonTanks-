// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public AMyPawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:

	class ATank* Tank ;

	void HandleDestruction() ;

private:
	UPROPERTY(EditAnywhere , Category = "Combat")
	float Distance = 300 ;

	FTimerHandle FireRateHandle;

	UPROPERTY(EditAnywhere , Category=" Combat")
	float FireRate = 2.0f ;

	void CheckForFire();

	bool InFireRange();
};
