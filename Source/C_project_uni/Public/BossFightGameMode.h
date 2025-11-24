// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BossFightGameMode.generated.h"

class APlayerTank;
class UBossFightGameInstance;
class UOnScreenMsg;

UCLASS()
class C_PROJECT_UNI_API ABossFightGameMode : public AGameModeBase
{
	GENERATED_BODY()
	ABossFightGameMode();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOnScreenMsg> ScreenMsgClass;

	UPROPERTY()
	UOnScreenMsg* ScreenMsgWidget;
	
	UPROPERTY()
	APlayerTank* PlayerTank; // player ref
	int32 EnemyCount;
	int32 TotalEnemyCount;
	bool isGameOver = false;
	bool isVictory = false;

	
	
	UFUNCTION()
	void OnPlayerDead(AActor* DeadActor);
	UFUNCTION()
	void OnEnemyDead(AActor* DeadActor);

	
private:
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bCanDebug = false;

	UPROPERTY(EditAnywhere)
	float GameOverDelay = 2;

	UPROPERTY(EditAnywhere)
	int32 CountDownDelay = 2;
	int32 CountDownSec;
	
	UPROPERTY()
	FTimerHandle GameOverTimer;
	
	UPROPERTY()
	UGameInstance* GameInstance;
	UPROPERTY()
	UBossFightGameInstance* BossFightGameInstance;
	
	FTimerHandle CountDownTimer;
	void OnGameOverTimerTimeOut();
	/* get all enemys in would
	 * get number of enemys
	 * bing on dead EVENT ( so we know when an enemy is dead )
	 */
	void GetSetAllEnemys();
	/*Get player ref
	 * bing player dead EVENT
	 */
	void GetSetPlayer();

	void OnCountDownTimerTimeOut();
	void OnGameOver();
};
