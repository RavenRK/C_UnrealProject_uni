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

	
	TArray<AActor*> Enemy; 	//define array & get all AEnemyTower in current world
	UGameplayStatics::GetAllActorsOfClass(this,AEnemyTower::StaticClass(),Enemy);
	EnemyCount = Enemy.Num();	//get number of enemy
	
	if (bCanDebug)
		UE_LOG(LogTemp, Display,TEXT("Number of Enemy: %d"), EnemyCount);

	//get player ref
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (PlayerPawn)
	{
		PlayerTank = Cast<APlayerTank>(PlayerPawn);
		if (!PlayerTank)
			UE_LOG(LogTemp,Display, TEXT("GameMode: Cast failed"));
	}
}
