// Fill out your copyright notice in the Description page of Project Settings.


#include "BossFightGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "EnemyTower.h"
#include "PlayerTank.h"
#include "HealthComp.h"

ABossFightGameMode::ABossFightGameMode()
{
	
}

void ABossFightGameMode::BeginPlay()
{
	Super::BeginPlay();
	
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
void ABossFightGameMode::OnEnemyDead(AActor* DeadActor)
{
	EnemyCount--;
	if (EnemyCount <= 0)
	{
		GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Green, TEXT("win"));
		GameOverString = "Victory";
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
	GameOverString = "Defeat";
	GetWorldTimerManager().SetTimer(GameOverTimer, this, &ABossFightGameMode::OnGameOverTimerTimeOut, GameOverDelay, false );

	//player dead restart level or something ?
	//maybe new player at check piont ?
}
void ABossFightGameMode::OnGameOverTimerTimeOut()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, *CurrentLevelName);
}
