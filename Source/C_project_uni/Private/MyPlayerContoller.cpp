// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerContoller.h"
#include "PlayerTank.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

void AMyPlayerContoller::BeginPlay()
{
	Super::BeginPlay();

}

void AMyPlayerContoller::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	InputSubsystem->AddMappingContext(MappingContext, 0);
}

void AMyPlayerContoller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerTank = Cast<APlayerTank>(InPawn);
	
	bShowMouseCursor = true;
	if (MoveAction && AttackAction && DogeAction && RotateAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this,&AMyPlayerContoller::HandleMove);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered,this,&AMyPlayerContoller::HandleRotate);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this,&AMyPlayerContoller::HandleAttack);
		EnhancedInputComponent->BindAction(DogeAction, ETriggerEvent::Triggered, this,&AMyPlayerContoller::HandleDoge);
	}
}

void AMyPlayerContoller::HandleMove(const FInputActionValue& IAValue)
{
	float Value = IAValue.Get<float>();
	FVector DeltaLocation = FVector(0,0,0);
	DeltaLocation.X = MoveSpeed * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	PlayerTank->AddActorLocalOffset(DeltaLocation, true);
	
	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Green, TEXT("move"));
}

void AMyPlayerContoller::HandleRotate(const FInputActionValue& IAValue)
{
	float Value = IAValue.Get<float>();
	FRotator DeltaRotation = FRotator(0,0,0);
	DeltaRotation.Yaw = RotateSpeed * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	PlayerTank->AddActorLocalRotation(DeltaRotation, true);
	
	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Green, TEXT("HandleRotate"));
}

void AMyPlayerContoller::HandleDoge()
{
	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Green, TEXT("HandleDoge"));
}

void AMyPlayerContoller::HandleAttack()
{
	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Green, TEXT("HandleAttack"));
}