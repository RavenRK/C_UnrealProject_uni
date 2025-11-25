// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerTank::APlayerTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	PickUpRange = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpRange"));
	PickUpRange->SetupAttachment(RootComponent);
}

void APlayerTank::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerEnabled(false);
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
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
	
	if (PC )//camera shake
		PC ->ClientStartCameraShake(HitCameraShakeClass);
	
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);
}

void APlayerTank::SetPlayerEnabled(bool Enabled) { bisAlive = Enabled; }

void APlayerTank::OnPawnHitEffect()
{
	Super::OnPawnHitEffect();
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, TEXT("we hit"));
	HitFeedBack();
	
	if (PC ) //camera shake
		PC ->ClientStartCameraShake(HitCameraShakeClass);
}

void APlayerTank::WeaponStatChange_Implementation(EMyEnum ProJType) {}
void APlayerTank::PlayerMoveFeedBack_Implementation() {}
void APlayerTank::PlayerStopMoveFeedBack_Implementation() {}
void APlayerTank::PlayerHitFeedBack_Implementation() {}
