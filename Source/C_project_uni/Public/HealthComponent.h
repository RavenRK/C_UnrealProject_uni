// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C_PROJECT_UNI_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Health")
	float maxHP = 100;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Health")
	float currentHP;

private:

	UFUNCTION(BlueprintCallable,Category="Health")
	void TakeDmg(float DmgAmount, float& Current_HP);
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	
};
