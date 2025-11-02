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
	APlayerTank* PlayerTank;
	int32 EnemyCount;
};
