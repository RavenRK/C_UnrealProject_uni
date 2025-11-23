// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProJDmgType/ElecDamageType.h"
#include "ProJDmgType/FireDmageType.h"
#include "ProJDmgType/IceDamageType.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseColl = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseColl"));
	BaseColl->SetupAttachment(RootComponent);

	ProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");

}

void AProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BaseColl->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::OnHitFeedBack_Implementation() { }
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	OnHitFeedBack();
	if (MyOwner)
	{
		if (OtherActor && OtherActor != MyOwner)
		{
			UGameplayStatics::ApplyDamage(OtherActor, ProJDmg, MyOwner->GetInstigatorController(),
				this,ProjDmgType());
		}
	}

	Destroy();
}

TSubclassOf<UDamageType> AProjectileBase::ProjDmgType()
{
	switch (ProjectileType)
	{
	case EMyEnum::NormalProJ:
		return UDamageType::StaticClass();
		
	case EMyEnum::FireProJ:
		return UFireDmageType::StaticClass();
		
	case EMyEnum::IceProJ:
		return UIceDamageType::StaticClass();
		
	case EMyEnum::ElecProJ:
		return UElecDamageType::StaticClass();
	}

	return UDamageType::StaticClass();
}

