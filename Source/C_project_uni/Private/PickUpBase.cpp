#include "PickUpBase.h"
#include "Components/SphereComponent.h"
#include "ProjectileBase.h"



APickUpBase::APickUpBase()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("BoxColl"));
	SetRootComponent(RootComponent);
}

void APickUpBase::BeginPlay()
{
	Super::BeginPlay();
	ChangePickUps(ProJRef);
}

void APickUpBase::ChangePickUps(TSubclassOf<AProjectileBase> NewProJRef)
{
	if (!NewProJRef) return;
	ProJRef = NewProJRef;
	StoredProjectileType = Cast<AProjectileBase>(NewProJRef->GetDefaultObject())->ProjectileType;
	ChangeVFX(StoredProjectileType);
}

void APickUpBase::ChangeVFX_Implementation(EMyEnum ProJType) {}
