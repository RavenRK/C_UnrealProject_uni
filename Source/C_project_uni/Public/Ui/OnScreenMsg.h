// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnScreenMsg.generated.h"


class UProgressBar;
class UTextBlock;

UCLASS()
class C_PROJECT_UNI_API UOnScreenMsg : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* MsgTextBlock;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* EnemiesBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* DeathCount;
	
	void SetOnScreenMsgText(FString Msg);
	void EnemyProgressUpdate(float TotalEnemies ,float CurrentEnemies);
	void PlayerDeathUpDate(int DeathCounter);
};
