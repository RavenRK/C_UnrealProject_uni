// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasePawn.h"
#include "PlayerTank.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class C_PROJECT_UNI_API APlayerTank : public AMyBasePawn
{
	GENERATED_BODY()
public:
	APlayerTank();
	bool bisAlive = true;
	
	UFUNCTION(BlueprintNativeEvent)
	void PlayerMoveFeedBack();

	UFUNCTION(BlueprintNativeEvent)
	void PlayerStopMoveFeedBack();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnPawnDestruction(AActor* DeadActor) override;
	void SetPlayerEnabled(bool Enabled);
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

};
