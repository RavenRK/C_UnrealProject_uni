// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasePawn.h"
#include "Components/BoxComponent.h"
#include "ProjectileBase.h"
#include "HealthComp.h"

AMyBasePawn::AMyBasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColl"));
	SetRootComponent(BoxComponent);
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(BoxComponent);
	
	TurrentMeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TurrentRoot"));
	TurrentMeshRoot->SetupAttachment(BaseMesh);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(TurrentMeshRoot);
	
	HealthCompo = CreateDefaultSubobject<UHealthComp>("HealthComp");
	
	ProJSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProJSpawnPoint"));
	ProJSpawnPoint->SetupAttachment(TurretMesh);
}

void AMyBasePawn::BeginPlay()
{
	Super::BeginPlay();

	HealthCompo->OnDeath.AddDynamic(this, &AMyBasePawn::OnPawnDestruction);
	HealthCompo->OnHit.BindDynamic(this, &AMyBasePawn::OnPawnHitEffect);
}

void AMyBasePawn::RotateTo(FVector Target)
{
	FVector VectorToTarget = Target - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0, VectorToTarget.Rotation().Yaw,0);

	FRotator InterpolatedRotation = FMath::RInterpTo
	(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		GetWorld()->GetDeltaSeconds(),
		10
	);
	
	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

void AMyBasePawn::Fire(float Dmg)
{
	FVector SpawnLocation = ProJSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProJSpawnPoint->GetComponentRotation();

	float YawSpread   = FMath::RandRange(-ProJSpreadAngle,ProJSpreadAngle);
	SpawnRotation.Yaw   += YawSpread;

	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProJBase,SpawnLocation,SpawnRotation);
	if (Projectile)
	{
		Projectile->SetOwner(this);
		Projectile->ProJDmg *= Dmg;
	}
	
	//DrawDebugSphere(GetWorld(), SpawnLocation,25, 12, FColor::Red, false, 2);
}

void AMyBasePawn::OnPawnDestruction(AActor* DeadActor)
{
	DeathFeedBack();
}

void AMyBasePawn::OnPawnHitEffect() {}
void AMyBasePawn::HitFeedBack_Implementation() {}
void AMyBasePawn::DeathFeedBack_Implementation() {}




