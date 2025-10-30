// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerContoller.generated.h"

struct FInputActionValue;
class APlayerCharacter;
class UInputAction;
class UEnhancedInputComponent;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS(Abstract) //you can’t instantiate it directly (in C++ or Blueprint)
class C_PROJECT_UNI_API AMyPlayerContoller : public APlayerController
{
	GENERATED_BODY()
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Movement Action")
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Movement Action")
	UInputAction* AttackAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Movement Action")
	UInputAction* DogeAction = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext = nullptr;
	
	// for more info (const FInputActionInstance& InputActionInstance
	void HandleMove(const FInputActionValue& InputActionValue);
	FVector2D MovementVector;
	void HandleDoge();
	void HandleAttack();
	
	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	UPROPERTY()
	APlayerCharacter* PlayerCharacter = nullptr;
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem;


 };
