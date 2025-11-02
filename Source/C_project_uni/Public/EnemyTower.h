// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasePawn.h"
#include "EnemyTower.generated.h"

class APlayerTank;
class USphereComponent;

UCLASS()
class C_PROJECT_UNI_API AEnemyTower : public AMyBasePawn
{
	GENERATED_BODY()

public:
	AEnemyTower();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	float AttackRange = 300;
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	APawn* PlayerTank;
private:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* AttackSphereRange;

	UFUNCTION()
	void OnSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
