// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplodeAOE.generated.h"

UCLASS()
class C_PROJECT_UNI_API AExplodeAOE : public AActor
{
	GENERATED_BODY()

public:
	AExplodeAOE();

	UPROPERTY(EditAnywhere)
	float Dmg;
	
	UFUNCTION(BlueprintNativeEvent)
	void AOEFeedBack();
protected:
	virtual void BeginPlay() override;

};
