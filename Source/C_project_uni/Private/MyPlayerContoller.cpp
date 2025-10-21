// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerContoller.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

void AMyPlayerContoller::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerContoller::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputWorldSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputWorldSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
		
	}
}
