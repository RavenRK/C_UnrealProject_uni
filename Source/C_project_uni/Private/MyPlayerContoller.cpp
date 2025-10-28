// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerContoller.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"

void AMyPlayerContoller::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerContoller::SetupInputComponent()
{
	Super::SetupInputComponent();
	
}

void AMyPlayerContoller::OnPossess(APawn* APawn)
{
	Super::OnPossess(APawn);

	PlayerCharacter = Cast<APlayerCharacter>(APawn);
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (MoveAction && AttackAction && DogeAction && LookAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this,&AMyPlayerContoller::HandleMove);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this,&AMyPlayerContoller::HandleAttack);
		EnhancedInputComponent->BindAction(DogeAction, ETriggerEvent::Triggered, this,&AMyPlayerContoller::HandleDoge);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,&AMyPlayerContoller::HandleLook);
	}
}

void AMyPlayerContoller::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	
}

void AMyPlayerContoller::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
}

void AMyPlayerContoller::HandleDoge()
{
	
}

void AMyPlayerContoller::HandleAttack()
{
	
}