// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"
#include "PlayerTank.h"


AEnemyTower::AEnemyTower()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector PlayerLocation =  PlayerTank->GetActorLocation();
	//RoateTO(PlayerLocation);
}

void AEnemyTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

