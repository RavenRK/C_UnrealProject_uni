// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffects.h"

#include "EnemyTower.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "HealthComp.h"
#include "PlayerTank.h"

#include "ProJDmgType/ElecDamageType.h"
#include "ProJDmgType/FireDmageType.h"
#include "ProJDmgType/IceDamageType.h"

void UStatusEffects::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UStatusEffects::OnDmgTaken_DmgEffect);
	HealthComp = GetOwner()->FindComponentByClass<UHealthComp>();
	
	ClassCheck();
	Owner = GetOwner();
}

void UStatusEffects::OnDmgTaken_DmgEffect(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageType->IsA(UFireDmageType::StaticClass()))
		FireEffect();
	else if (DamageType->IsA(UIceDamageType::StaticClass()))
		IceEffect();
	else if (DamageType->IsA(UElecDamageType::StaticClass()))
		ElectricEffect();
}

void UStatusEffects::BurnDmgStart()
{
	HealthComp->TakeDmg(BurnDmg);
	
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green
		,FString::Printf(TEXT("taking burn dmg %f"), HealthComp->CurrentHealth));
	
	float Value = FMath::FRandRange(100, 0.f);
	if (Value < ExplodeChancePercentage)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green
	,FString::Printf(TEXT("Boom")));
	}
}
void UStatusEffects::BurnDmgEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(BurnTimerStart);
	FireEnd();
}

void UStatusEffects::FireEffect()
{
	GetWorld()->GetTimerManager().SetTimer
	(BurnTimerStart, this, &UStatusEffects::BurnDmgStart, BurnTickRate, true);
	
	GetWorld()->GetTimerManager().SetTimer
	(BurnTimerEnd, this, &UStatusEffects::BurnDmgEnd, BurnDuration, false);
	FireFeedBack();
}

void UStatusEffects::IceEffect()
{
	ClassCheck();

	OriginalStatsIce();
	
	IceEffectStat();
	
	GetWorld()->GetTimerManager().SetTimer
	(IceTimer, this, &UStatusEffects::OriginalStatsIce, IceTimerDuration, false);
	ElectricFeedBack();
}

void UStatusEffects::OriginalStatsIce()
{
	if (PlayerTank)
	{
		OriginalMoveSpeed = PlayerTank->MoveSpeed;
		OriginalRotateSpeed = PlayerTank->RotateSpeed;
		OriginalAttackSpeed = PlayerTank->AttackSpeed;
	}
	else if (EnemyTower)
	{
		OriginalEnemyFireRate = EnemyTower->FireRate;
		OriginalEnemyTurnRate = EnemyTower->TurnRate;
	}
}

void UStatusEffects::IceEffectStat()
{
	if (bEnemyOrPlayer)
	{
		PlayerTank->MoveSpeed /= MovementSlowPercentage;
		PlayerTank->RotateSpeed /= RotateSlowPercentage;
		PlayerTank->AttackSpeed /= AttackSpeedSlowPercentage;
	}
	else
	{
		EnemyTower->FireRate /= AttackSpeedSlowPercentage;
		EnemyTower->TurnRate = 0.05;
	}
}

void UStatusEffects::ClassCheck()
{
	Owner = GetOwner();

	PlayerTank = nullptr;
	EnemyTower = nullptr;

	if (Owner->IsA(AEnemyTower::StaticClass()))
	{
		EnemyTower = Cast<AEnemyTower>(Owner);
	}
	else if (Owner->IsA(APlayerTank::StaticClass()))
	{
		PlayerTank = Cast<APlayerTank>(Owner);
	}
}

void UStatusEffects::ElectricEffect()
{
	//CC timer

	//spawn dmg area

	IceFeedBack();
}


// Player Feed Back
void UStatusEffects::ExplodeFeedBack_Implementation() {}
void UStatusEffects::AOEDmgFeedBack_Implementation() {}

void UStatusEffects::FireFeedBack_Implementation() {}
void UStatusEffects::FireEnd_Implementation() {}

void UStatusEffects::IceFeedBack_Implementation() {}
void UStatusEffects::ElectricFeedBack_Implementation() {}
