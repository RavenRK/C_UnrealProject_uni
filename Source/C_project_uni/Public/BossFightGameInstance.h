// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BossFightGameInstance.generated.h"

UCLASS()
class C_PROJECT_UNI_API UBossFightGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 MaxLevelIndex = 4;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentLevelIndex = 1;

	void LoadNextLevel();
	void RestartCurrentLevel();
	void RestartGame();

	int PlayerDeathCounter = 0;

private:
	void ChangeLevel(int32 Index);
};
