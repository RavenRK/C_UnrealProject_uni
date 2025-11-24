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
	
	//90% sure I don't need this
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = "Stats")
	float FireRate = .5f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float AttackRange = 700;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float TurnRate = 0.01f;
	
protected:
	UPROPERTY(VisibleAnywhere)
	bool bTowerCanRotate = false;
	UPROPERTY(VisibleAnywhere)
	bool bCanFire = false;
	
	UPROPERTY()
	FTimerHandle FireTimerHandle;
	UPROPERTY()
	FTimerHandle RotateToPlayerTimerHandle;
	
	UPROPERTY()
	APlayerTank* PlayerTank;

	virtual void OnPawnDestruction(AActor* DeadActor) override;
	
	virtual void BeginPlay() override;
	virtual void FireProJ();
	void RotateToPlayer();
	
private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* AttackSphereRange;
	
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnSphereBeginOverlap
	(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	UFUNCTION()
	void OnSphereEndOverlap
	(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	void StopAttackTimer();

};
