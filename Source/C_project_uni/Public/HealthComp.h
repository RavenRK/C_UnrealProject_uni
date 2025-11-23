// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComp.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C_PROJECT_UNI_API UHealthComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComp();
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 100.f;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, AActor*, DeadActor);
	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath;
	
	void TakeDmg(float Dmg);
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CurrentHealth;
protected:
		

	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnDmgTaken
	( AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser );

	virtual void Death();


};
