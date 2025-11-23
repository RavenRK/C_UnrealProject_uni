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

		ExplodeFeedBack();
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
	ElectricFeedBackStart();
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
	IceFeedBackEnd();
}

void UStatusEffects::IceEffectStat()
{
	if (PlayerTank)
	{
		PlayerTank->MoveSpeed /= MovementSlowPercentage;
		PlayerTank->RotateSpeed /= RotateSlowPercentage;
		PlayerTank->AttackSpeed /= AttackSpeedSlowPercentage;
	}
	else if (EnemyTower)
	{
		EnemyTower->FireRate /= AttackSpeedSlowPercentage;
		EnemyTower->TurnRate = 0.05;
	}
	IceFeedBackStart();
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
	
	ElectricFeedBackStart();
}

//AMO
void UStatusEffects::ExplodeFeedBack_Implementation() {}
void UStatusEffects::AOEDmgFeedBack_Implementation() {}
//Fire
void UStatusEffects::FireFeedBack_Implementation() {}
void UStatusEffects::FireEnd_Implementation() {}
//Ice
void UStatusEffects::IceFeedBackStart_Implementation() {}
void UStatusEffects::IceFeedBackEnd_Implementation() {}
//elec
void UStatusEffects::ElectricFeedBackStart_Implementation() {}
void UStatusEffects::ElectricFeedBackEnd_Implementation() {}