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
	
	Owner = GetOwner();
}

void UStatusEffects::OnDmgTaken_DmgEffect(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageType->IsA(UFireDmageType::StaticClass()))
	{
		if (bBurning) {return;}
		
		FireEffect();
		bBurning = true;
	}
	else if (DamageType->IsA(UIceDamageType::StaticClass()))
	{
		if (bIceing) {return;}
		
		IceEffect();
		bIceing = true;
	}
	else if (DamageType->IsA(UElecDamageType::StaticClass()))
	{
		//if (bElecing) {return;}
		
		ElectricEffect();
		//bElecing = true;
	}

}

void UStatusEffects::BurnDmgStart()
{
	HealthComp->TakeDmg(BurnDmg);
	
	//GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,FString::Printf(TEXT("taking burn dmg %f"), HealthComp->CurrentHealth));
	
	float Value = FMath::FRandRange(100, 0.f);
	if (Value < ExplodeChancePercentage)
	{
		//GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,FString::Printf(TEXT("Boom")));

		ExplodeFeedBack();
	}
}
void UStatusEffects::BurnDmgEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(BurnTimerStart);
	FireEnd();
	bBurning = false;
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
	//is player ir enemy ?
	//get there original stat
	IceSetUp();

	//apply ice effect
	IceEffectStat();
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, TEXT("we slow"));
	
	//remove when timer over
	GetWorld()->GetTimerManager().SetTimer
	(IceTimer, this, &UStatusEffects::IceEffectOverTimer, IceTimerDuration, false);
}

void UStatusEffects::IceSetUp()
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
	//set them to slow speed
	if (PlayerTank)
	{
		PlayerTank->MoveSpeed *= MovementSlowPercentage;
		PlayerTank->RotateSpeed *= RotateSlowPercentage;
		PlayerTank->AttackSpeed *= AttackSpeedSlowPercentage;
	}
	else if (EnemyTower)
	{
		EnemyTower->FireRate *= AttackSpeedSlowPercentage;
		EnemyTower->TurnRate = RotateSlowPercentage;
	}
	IceFeedBackStart();
}

void UStatusEffects::IceEffectOverTimer()
{
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, TEXT("normal ?"));

	// we ice effectsing ?
	if (bIceing)
	{
		//set them to normal speed
		if (PlayerTank)
		{
			PlayerTank->MoveSpeed = OriginalMoveSpeed;
			PlayerTank->RotateSpeed = OriginalRotateSpeed;
			PlayerTank->AttackSpeed = OriginalAttackSpeed;
		}
		else if (EnemyTower)
		{
			EnemyTower->FireRate = OriginalEnemyFireRate;
			EnemyTower->TurnRate = OriginalEnemyTurnRate;
		}
		bIceing = false;
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