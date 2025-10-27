// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "MyCustomCharacter.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class C_PROJECT_UNI_API AMyCustomCharacter : public APawn
{
	GENERATED_BODY()

public:
	AMyCustomCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	float MS_movementSpeed = 25;

	
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
