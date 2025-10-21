// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCustomCharacter.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum EMyEnum : uint8
{
	Run        UMETA(DisplayName = "Move"),
	Dodge       UMETA(DisplayName = "Dodge"),
	Attack      UMETA(DisplayName = "Attack"),
	None        UMETA(DisplayName = "None")
};

UCLASS()
class C_PROJECT_UNI_API APlayerCharacter : public AMyCustomCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	


protected:
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly)
	//TObjectPtr<USpringArmComponent> SpringArmComponent;

	//UPROPERTY(EditDefaultsOnly)
	//TObjectPtr<UCameraComponent> CameraComponent;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void PlayerMovement(FVector2D InputValue);

private:
	FVector2D LastInputValue;
};
