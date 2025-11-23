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
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0) {Death();}
}

void UHealthComp::Death()
{
	
	OnDeath.Broadcast(GetOwner());
	//GetOwner()->Destroy();
}
