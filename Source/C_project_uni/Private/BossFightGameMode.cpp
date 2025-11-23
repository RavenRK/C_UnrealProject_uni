// Fill out your copyright notice in the Description page of Project Settings.


#include "BossFightGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "EnemyTower.h"
#include "PlayerTank.h"
#include "HealthComp.h"
#include "BossFightGameInstance.h"

ABossFightGameMode::ABossFightGameMode()
{
	
}

void ABossFightGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GameInstance = GetGameInstance();
	
	if (GameInstance)
		BossFightGameInstance =Cast<UBossFightGameInstance>(GameInstance);
	
	GetAllEnemys();
	GetPlayer();
}

#pragma region EnemyHandling

void ABossFightGameMode::GetAllEnemys()
{
	TArray<AActor*> EnemyTowers; 	//define array & get all AEnemyTower in current world
	UGameplayStatics::GetAllActorsOfClass(this,AEnemyTower::StaticClass(),EnemyTowers);

	//get number of enemy & print to Logtemp
	EnemyCount = EnemyTowers.Num();
	if (bCanDebug) UE_LOG(LogTemp, Display,TEXT("Number of Enemy: %d"), EnemyCount);

	//loop and bing all the OnDeath events, so I know when an enemy is dead
	for (AActor* EnemyActor : EnemyTowers)
	{
		if (UHealthComp* HealthComp = EnemyActor->FindComponentByClass<UHealthComp>())
			HealthComp->OnDeath.AddDynamic(this, &ABossFightGameMode::OnEnemyDead);
	}
	
}

#pragma endregion EnemyHandling
#pragma region PlayerSetup
void ABossFightGameMode::GetPlayer()
{
	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0))
	{
		PlayerTank = Cast<APlayerTank>(PlayerPawn);
		if (PlayerTank)
		{
			if (UHealthComp* PlayerHealth = PlayerTank->FindComponentByClass<UHealthComp>())
				PlayerHealth->OnDeath.AddDynamic(this, &ABossFightGameMode::OnPlayerDead);
		}
	}
}
#pragma endregion PlayerSetup

void ABossFightGameMode::OnPlayerDead(AActor* DeadActor)
{
	isVictory = true;
	GetWorldTimerManager().SetTimer(GameOverTimer, this, &ABossFightGameMode::OnGameOver,
		GameOverDelay, false );
}
void ABossFightGameMode::OnEnemyDead(AActor* DeadActor)
{
	EnemyCount--;
	if (EnemyCount <= 0)
	{
		isVictory = false;
		GetWorldTimerManager().SetTimer(GameOverTimer, this, &ABossFightGameMode::OnGameOver,
			GameOverDelay, false );
	}
}

void ABossFightGameMode::OnGameOver()
{
	if (isVictory)
		BossFightGameInstance->RestartCurrentLevel();
	else 
		BossFightGameInstance->LoadNextLevel();
}


void ABossFightGameMode::OnGameOverTimerTimeOut()
{

}
