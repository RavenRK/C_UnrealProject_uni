// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UENUM(BlueprintType)
enum EMyEnum : uint8
{
	Run        UMETA(DisplayName = "Move"),
	Dodge       UMETA(DisplayName = "Dodge"),
	Attack      UMETA(DisplayName = "Attack"),
	None        UMETA(DisplayName = "None")
};

UCLASS()
class C_PROJECT_UNI_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	

};
