// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerTank::APlayerTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

void APlayerTank::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void APlayerTank::OnPawnDestruction(AActor* DeadActor)
{
	Super::OnPawnDestruction(DeadActor);

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);
	bisAlive = false;
}

void APlayerTank::SetPlayerEnabled(bool Enabled)
{
	APlayerController* PlayerContoller = Cast<APlayerController>(GetController());
}

void APlayerTank::PlayerMoveFeedBack_Implementation() {}
void APlayerTank::PlayerStopMoveFeedBack_Implementation() {}