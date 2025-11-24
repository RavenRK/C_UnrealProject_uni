// Fill out your copyright notice in the Description page of Project Settings.


#include "BossFightGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "EnemyTower.h"
#include "PlayerTank.h"
#include "HealthComp.h"
#include "BossFightGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "Ui/OnScreenMsg.h"

ABossFightGameMode::ABossFightGameMode()
{
	
}

void ABossFightGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GameInstance = GetGameInstance();
	
	if (GameInstance)
		BossFightGameInstance =Cast<UBossFightGameInstance>(GameInstance);
	
	GetSetAllEnemys();
	GetSetPlayer();
	
	APlayerController* PlayerController =
		UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ScreenMsgWidget = CreateWidget<UOnScreenMsg>(PlayerController, ScreenMsgClass);
		if (ScreenMsgWidget)
		{
			ScreenMsgWidget->AddToPlayerScreen();
			ScreenMsgWidget->SetOnScreenMsgText("Read!?");
		}
	}
	
	CountDownSec = CountDownDelay;
	GetWorldTimerManager().SetTimer(CountDownTimer, this,
		&ABossFightGameMode::OnCountDownTimerTimeOut,1.0f,true);
	ScreenMsgWidget->PlayerDeathUpDate(BossFightGameInstance->PlayerDeathCounter);
}

void ABossFightGameMode::OnCountDownTimerTimeOut()
{
	CountDownSec--;
	if (CountDownSec > 0)
	{
		ScreenMsgWidget->SetOnScreenMsgText("Set~");
	}
	else if (CountDownSec == 0)
	{
		ScreenMsgWidget->SetOnScreenMsgText("Go!!");
	}
	else if (CountDownSec < 0)
	{
		ScreenMsgWidget->MsgTextBlock->SetVisibility(ESlateVisibility::Hidden);
		PlayerTank->SetPlayerEnabled(true);
		GetWorldTimerManager().ClearTimer(CountDownTimer);
	}
}

#pragma region EnemyHandling

void ABossFightGameMode::GetSetAllEnemys()
{
	TArray<AActor*> EnemyTowers; 	//define array & get all AEnemyTower in current world
	UGameplayStatics::GetAllActorsOfClass(this,AEnemyTower::StaticClass(),EnemyTowers);

	//get number of enemy & print to Logtemp
	EnemyCount = EnemyTowers.Num();
	TotalEnemyCount = EnemyCount;
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
void ABossFightGameMode::GetSetPlayer()
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
		ScreenMsgWidget->MsgTextBlock->SetVisibility(ESlateVisibility::Visible);
		ScreenMsgWidget->SetOnScreenMsgText("Lose ( try again T^T )");
	
		BossFightGameInstance->PlayerDeathCounter++;
		ScreenMsgWidget->PlayerDeathUpDate(BossFightGameInstance->PlayerDeathCounter);
	
	GetWorldTimerManager().SetTimer(GameOverTimer, this, &ABossFightGameMode::OnGameOver,
		GameOverDelay, false );
}
void ABossFightGameMode::OnEnemyDead(AActor* DeadActor)
{
	EnemyCount--;
	ScreenMsgWidget->EnemyProgressUpdate(TotalEnemyCount, EnemyCount);
	if (EnemyCount <= 0)
	{
		isVictory = false;
		ScreenMsgWidget->MsgTextBlock->SetVisibility(ESlateVisibility::Visible);
		ScreenMsgWidget->SetOnScreenMsgText("Win!!!");
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
