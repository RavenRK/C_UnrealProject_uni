#include "HealthComp.h"

UHealthComp::UHealthComp()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = MaxHealth;
}


void UHealthComp::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComp::OnDmgTaken);
}

// this get called when the owner gets hit by something ( player / enemy )
void UHealthComp::OnDmgTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	OnHit.Execute();
	TakeDmg(Damage);
}

void UHealthComp::Death()
{
	if (bIsDead) {return;}
	bIsDead = true;
	OnDeath.Broadcast(GetOwner());
	//GetOwner()->Destroy();
}

void UHealthComp::TakeDmg(float Dmg)
{
	CurrentHealth -= Dmg;
	if (CurrentHealth <= 0)
	{
		Death();
	}
}
