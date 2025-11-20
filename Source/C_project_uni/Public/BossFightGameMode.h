// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BossFightGameMode.generated.h"

class APlayerTank;

UCLASS()
class C_PROJECT_UNI_API ABossFightGameMode : public AGameModeBase
{
	GENERATED_BODY()
	ABossFightGameMode();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	APlayerTank* PlayerTank; // player ref
	int32 EnemyCount;

	UFUNCTION()
	void OnPlayerDead(AActor* DeadActor);
	UFUNCTION()
	void OnEnemyDead(AActor* DeadActor);
private:
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bCanDebug = false;

	/* get all enemys in would
	 * get number of enemys
	 * bing on dead EVENT ( so we know when an enemy is dead )
	 */
	void GetAllEnemys();
	/*Get player ref
	 * bing player dead EVENT
	 */
	void GetPlayer();
};
