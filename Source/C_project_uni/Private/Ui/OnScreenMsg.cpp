// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/OnScreenMsg.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UOnScreenMsg::SetOnScreenMsgText(FString Msg)
{
	FText MsgText = FText::FromString(Msg);
	MsgTextBlock->SetText(MsgText);
}

void UOnScreenMsg::EnemyProgressUpdate(float TotalEnemies, float CurrentEnemies)
{
	if (TotalEnemies <= 0) return;
	float EnemyPercent = (float)CurrentEnemies / (float)TotalEnemies;
	EnemiesBar->SetPercent(EnemyPercent);
}

void UOnScreenMsg::PlayerDeathUpDate(int DeathCounter)
{
	FString Msg = FString::Printf(TEXT("Player Death Count: %d"), DeathCounter);
	FText MsgText = FText::FromString(Msg);

	DeathCount->SetText(MsgText);
}

