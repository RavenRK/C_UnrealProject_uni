// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"
#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"


AEnemyTower::AEnemyTower()
{
	PrimaryActorTick.bCanEverTick = true;

	//set up attack range sphere
	AttackSphereRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	AttackSphereRange->SetSphereRadius(AttackRange);
	AttackSphereRange->SetupAttachment(RootComponent);
	
}

void AEnemyTower::OnPawnDestruction(AActor* DeadActor)
{
	Super::OnPawnDestruction(DeadActor);
	Destroy();
}

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AEnemyTower::FireProJ()
{
	if (PlayerTank && bCanFire)
	{
		if (!PlayerTank->bisAlive)
			{ StopAttackTimer(); return;}
		
		//spawn VFX
		//play sound
		Fire(DmgMultiplier);

	}
}

void AEnemyTower::RotateToPlayer()
{
	if (PlayerTank && bTowerCanRoate)
		RotateTo(PlayerTank->GetActorLocation());
}

void AEnemyTower::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (AttackSphereRange)	//set up overlap event
	{
		AttackSphereRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemyTower::OnSphereBeginOverlap);
		AttackSphereRange->OnComponentEndOverlap.AddDynamic(this, &AEnemyTower::OnSphereEndOverlap);
	}
}

//when player is in range 
void AEnemyTower::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!PlayerTank) return;
	if (!PlayerTank->bisAlive) return;
	
	bTowerCanRoate = true;
	bCanFire = true;

	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AEnemyTower::FireProJ, FireRate, true);
	GetWorldTimerManager().SetTimer(RotateToPlayerTimerHandle, this, &AEnemyTower::RotateToPlayer, TurnRate, true);
}

void AEnemyTower::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!PlayerTank) return;
	StopAttackTimer();
}

void AEnemyTower::StopAttackTimer()
{
	bTowerCanRoate = false;
	bCanFire = false;
	
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(RotateToPlayerTimerHandle);
}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


