// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasePawn.h"
#include "EnemyTower.generated.h"

class APlayerTank;

UCLASS()
class C_PROJECT_UNI_API AEnemyTower : public AMyBasePawn
{
	GENERATED_BODY()

public:
	AEnemyTower();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerTank* PlayerTank;
private:
	
};
