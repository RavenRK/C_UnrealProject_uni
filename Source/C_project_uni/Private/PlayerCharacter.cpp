// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GameFramework/PawnMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::PlayerMovement(FVector2D InputValue)
{
	LastInputValue.X = InputValue.X;
	LastInputValue.Y = InputValue.Y;

	FRotator MovementDirection = FRotator(0, GetControlRotation().Yaw, GetControlRotation().Roll);
	GetMovementComponent()->AddInputVector(MovementDirection.RotateVector(FVector::ForwardVector) * InputValue.X);
	GetMovementComponent()->AddInputVector(MovementDirection.RotateVector(FVector::ForwardVector) * InputValue.Y);

}

