// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerTank.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerContoller.generated.h"

struct FInputActionInstance; // more info then V
struct FInputActionValue;	 // less info then ^ just the value
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Action")
	UInputAction* PickUpAction = nullptr;
	
protected:

	UPROPERTY()
	FTimerHandle AttackSpeedTimer;
	UPROPERTY()
	FTimerHandle FirstShotCDTimer;
	bool bCanAttack = true;
	void Attack();
	void FirstShotCD();
	
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
	void MoveCompleted();
	void EndAttackTimer();
	void PickUp();


	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;
	
	UPROPERTY()
	TArray<AActor*> Overlaps;
	
	UPROPERTY()
	EMyEnum StoredProjectileType;
private:
	UPROPERTY() UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	UPROPERTY() APlayerTank* PlayerTank = nullptr;
	UPROPERTY() UEnhancedInputLocalPlayerSubsystem* InputSubsystem;

	void PlayerWeaponChnage(EMyEnum ProjectileType);
 };
