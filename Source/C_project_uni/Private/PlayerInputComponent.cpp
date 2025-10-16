// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

UPlayerInputComponent::UPlayerInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	// Bind actions to bindings
	if (MoveAction && AttackAction && DodgeAction)
	{
		EnhInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UPlayerInputComponent::Move);
		EnhInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &UPlayerInputComponent::Attack);
		EnhInputComponent->BindAction(DodgeAction, ETriggerEvent::Completed, this, &UPlayerInputComponent::Dodge);
	}
	else   {checkf(false, TEXT("One or more input actions were not specified."));}
}

void UPlayerInputComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UPlayerInputComponent::Move(const FInputActionValue& InputActionValue)
{
	
}

void UPlayerInputComponent::Attack()
{
	
}

void UPlayerInputComponent::Dodge()
{
	
}

void UPlayerInputComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

