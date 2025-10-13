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
	// Sets default values for this pawn's properties
	APlayerCharacter();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
