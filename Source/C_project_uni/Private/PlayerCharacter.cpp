// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "MyPlayerContoller.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment((RootComponent));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	bUseControllerRotationYaw = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OldRotation = FRotator(GetActorRotation());
	if (bISUsingMouse)
	{
		if (!My_PController_Ref)
			return;

		FHitResult Hit;
		if (My_PController_Ref->GetHitResultUnderCursorByChannel(TraceChannel,true,Hit))
		{
			const FVector HitLocation = Hit.Location;
			const FVector OwnerLocation = GetActorLocation();

			FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, HitLocation);

			AnimAngle = LookAt.Yaw;

			FRotator NewRotation = FRotator(OldRotation.Pitch, AnimAngle, OldRotation.Roll);
			SetActorRotation(NewRotation);
		}
		else
		{
			FRotator NewRotation = FRotator(OldRotation.Pitch, AnimAngle, OldRotation.Roll);
			SetActorRotation(NewRotation);
		}
	}
}


