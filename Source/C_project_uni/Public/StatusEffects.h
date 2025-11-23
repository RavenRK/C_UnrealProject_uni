// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusEffects.generated.h"

class AEnemyTower;
class APlayerTank;
class UHealthComp;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C_PROJECT_UNI_API UStatusEffects : public UActorComponent
{
	GENERATED_BODY()

public:
	//Fire Effect
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Fire")
	float BurnDmg = 1.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Fire")
	float BurnTickRate = .25;
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Fire")
	float BurnDuration = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Fire")
	float ExplodeChancePercentage = 5;
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Fire")
	float ExplodeDmg = 30;
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Fire")
	float ExplodeAOERange = 150;
	
	UFUNCTION(BlueprintNativeEvent)
	void ExplodeFeedBack();
	UFUNCTION(BlueprintNativeEvent)
	void FireFeedBack();
	UFUNCTION(BlueprintNativeEvent)
	void FireEnd();
	
	UFUNCTION()
	void FireEffect();
	void BurnDmgStart();
	void BurnDmgEnd();
	
	UPROPERTY()
	FTimerHandle BurnTimerStart;
	UPROPERTY()
	FTimerHandle BurnTimerEnd;
	
	//Ice Effect
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Ice")
	float AttackSpeedSlowPercentage;
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Ice")
	float MovementSlowPercentage = .35;
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Ice")
	float RotateSlowPercentage;

	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Ice")
	float IceTimerDuration = 4;
	
	UFUNCTION(BlueprintNativeEvent)
	void IceFeedBack();
	UFUNCTION()
	void IceEffect();
	
	UPROPERTY()
	FTimerHandle IceTimer;
	void OriginalStatsIce();
	void IceEffectStat();
	
	bool bEnemyOrPlayer;
	
	UPROPERTY()
	APlayerTank* PlayerTank;
	UPROPERTY()
	AEnemyTower* EnemyTower;
	UPROPERTY()
	AActor* Owner;
	
	void ClassCheck();
	
	//Electric Effect
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Electric")
	float CCDuration;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Electric")
	float AOEShockDmg;
	UPROPERTY(EditDefaultsOnly, Category = "Effects Stats | Electric")
	float AOEDmgRange;

	UFUNCTION(BlueprintNativeEvent)
	void AOEDmgFeedBack();
	UFUNCTION(BlueprintNativeEvent)
	void ElectricFeedBack();
	UFUNCTION()
	void ElectricEffect();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	virtual void OnDmgTaken_DmgEffect
	( AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser );

	UPROPERTY()
	UHealthComp* HealthComp;

	float OriginalMoveSpeed;
	float OriginalRotateSpeed;
	float OriginalAttackSpeed;

	float OriginalEnemyFireRate;
	float OriginalEnemyTurnRate;
};
