// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"
#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"


AEnemyTower::AEnemyTower()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackSphereRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	AttackSphereRange->SetSphereRadius(AttackRange);
	AttackSphereRange->SetupAttachment(RootComponent);


}

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();
	AttackSphereRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemyTower::OnSphereBeginOverlap);
	
	PlayerTank = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	PlayerTank = Cast<APlayerTank>(PlayerTank);
}

void AEnemyTower::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(2, .1f, FColor::Green, TEXT("in range"));

}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerTank)
		RoateTO(PlayerTank->GetActorLocation());
}

void AEnemyTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

