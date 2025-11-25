// Fill out your copyright notice in the Description page of Project Settings.


#include "BossFightGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBossFightGameInstance::ChangeLevel(int32 Index)
{
	if (Index > 0 && Index <= MaxLevelIndex)
	{
		CurrentLevelIndex = Index;

		FString LevelNameString = FString::Printf(TEXT("Test_Level%d"), CurrentLevelIndex);
		UGameplayStatics::OpenLevel(GetWorld(), *LevelNameString);
	}
}

void UBossFightGameInstance::LoadNextLevel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("here"));

	if (CurrentLevelIndex < MaxLevelIndex)
		ChangeLevel(CurrentLevelIndex + 1);
	else
		RestartGame();
}

void UBossFightGameInstance::RestartCurrentLevel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("restart level"));
	ChangeLevel(CurrentLevelIndex);
}

void UBossFightGameInstance::RestartGame()
{
	ChangeLevel(1);
}
