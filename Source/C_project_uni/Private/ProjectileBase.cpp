// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	ProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	
	ProjMoveComp->InitialSpeed = StartSpeed;
	ProjMoveComp->MaxSpeed = MaxSpeed;
}

void AProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		if (OtherActor && OtherActor != MyOwner)
		{
			UGameplayStatics::ApplyDamage(OtherActor, ProJDmg, MyOwner->GetInstigatorController(),
				this,UDamageType::StaticClass());
		}
	}

	Destroy();
}

