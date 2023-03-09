// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public AMyPawn
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm ;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true"))
	class UCameraComponent* Camera ;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed;

	void Move(float input);
	void Turn(float Input);

	class APlayerController* PlayerController; 


public:
	ATank();

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

	APlayerController* GetPlayerController(){ return PlayerController ;}

	bool TankAlive = true;
};
