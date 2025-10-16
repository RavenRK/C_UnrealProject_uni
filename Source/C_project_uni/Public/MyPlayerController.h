// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class C_PROJECT_UNI_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();
	
	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* AttackAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input|Actions")
	UInputAction* DodgeAction;
	
protected:
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& InputActionValue);
	void Attack();
	void Dodge();
};
