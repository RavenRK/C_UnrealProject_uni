// Fill out your copyright notice in the Description page of Project Settings.


#include "BossFightGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "EnemyTower.h"
#include "PlayerTank.h"

ABossFightGameMode::ABossFightGameMode()
{
	
}

void ABossFightGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> EnemyTowers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AEnemyTower::StaticClass(),EnemyTowers);
	TowerCount = EnemyTowers.Num();
	UE_LOG(LogTemp, Display,TEXT("Number of Enemy: %d"), TowerCount);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (PlayerPawn)
	{
		PlayerTank = Cast<APlayerTank>(PlayerPawn);
		if (!PlayerTank)
		UE_LOG(LogTemp,Display, TEXT("GameMode: Cast failed"));
	}
	
}
