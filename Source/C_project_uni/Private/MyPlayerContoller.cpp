// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerContoller.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

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
	PlayerCharacter = Cast<APlayerCharacter>(InPawn);
	
	bShowMouseCursor = true;
	if (MoveAction && AttackAction && DogeAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this,&AMyPlayerContoller::HandleMove);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this,&AMyPlayerContoller::HandleAttack);
		EnhancedInputComponent->BindAction(DogeAction, ETriggerEvent::Triggered, this,&AMyPlayerContoller::HandleDoge);
	}
}

void AMyPlayerContoller::HandleMove(const FInputActionValue& InputActionValue)
{
	MovementVector = InputActionValue.Get<FVector2D>();
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(),MovementVector.Y);
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(),MovementVector.X);

	
}

void AMyPlayerContoller::HandleDoge()
{
	FVector forwardVector = PlayerCharacter->GetActorForwardVector();

	if ( GEngine)
	{
		FString Msg = FString::Printf(TEXT("doge: X=%f, Y=%f"), forwardVector.X, forwardVector.Y);
		GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Green, Msg);
	}

}

void AMyPlayerContoller::HandleAttack()
{
	FVector forwardVector = PlayerCharacter->GetActorForwardVector();

	if ( GEngine)
	{
		FString Msg = FString::Printf(TEXT("attack: X=%f, Y=%f"), forwardVector.X, forwardVector.Y);
		GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Green, Msg);
	}
}