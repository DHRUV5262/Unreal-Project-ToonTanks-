// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank(){

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
    PlayerController = Cast<APlayerController>(GetController());
    TankAlive = true;
}
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(PlayerController != nullptr){
        FHitResult HitResult;
        PlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult );
        GetRotation(HitResult.ImpactPoint);
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this , &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this , &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire") ,IE_Pressed , this , &ATank::Fire);
}

void ATank::Move(float Input){
    float Time = UGameplayStatics::GetWorldDeltaSeconds(this);
    FVector Move(0.0f) ;
    Move.X = Input * Speed * Time ;
    AddActorLocalOffset(Move ,true);
}

void ATank::Turn(float Input){
    float Time = UGameplayStatics::GetWorldDeltaSeconds(this);
    FRotator Turn = FRotator::ZeroRotator ;
    Turn.Yaw = Input * TurnSpeed * Time ;
    AddActorLocalRotation(Turn , true);
}

void ATank::HandleDestruction(){
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    TankAlive = false;
}