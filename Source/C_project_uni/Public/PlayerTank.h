// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasePawn.h"
#include "PlayerTank.generated.h"

class USphereComponent;
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
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* PickUpRange;
	
	UFUNCTION(BlueprintNativeEvent)
	void WeaponStatChange(EMyEnum ProJType);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats | Movement")
	float MoveSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats | Movement")
	float RotateSpeed = 75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats | Attack")
	float AttackSpeed = .5f;
		
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
