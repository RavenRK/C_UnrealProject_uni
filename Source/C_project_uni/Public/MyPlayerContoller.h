// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerContoller.generated.h"

struct FInputActionInstance; // more info then V
struct FInputActionValue; // less info then ^ just the value
class APlayerTank;
class UInputAction;
class UEnhancedInputComponent;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS(Abstract) //you can’t instantiate it directly (in C++ or Blueprint)
class C_PROJECT_UNI_API AMyPlayerContoller : public APlayerController
{
	GENERATED_BODY()
public:
	//Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Action")
	UInputAction* MoveAction = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Action")
	UInputAction* AttackAction = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Action")
	UInputAction* RotateAction = nullptr;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext = nullptr;
	
	// more info (const FInputActionInstance& InputActionInstance
	// for Value (const FInputActionValue& IAValue);
	FVector2D MovementVector;
	void HandleMove(const FInputActionValue& IAValue);
	void HandleRotate(const FInputActionValue& IAValue);
	void HandleAttack();

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 300;
	UPROPERTY(EditAnywhere)
	float RotateSpeed = 75;
	
	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;

private:
	UPROPERTY() UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	UPROPERTY() APlayerTank* PlayerTank = nullptr;
	UPROPERTY() UEnhancedInputLocalPlayerSubsystem* InputSubsystem;


 };
