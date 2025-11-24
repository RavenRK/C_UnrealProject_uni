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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, AActor*, DeadActor);
	DECLARE_DYNAMIC_DELEGATE(FOnHitSignature);
	
	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath;
	UPROPERTY()
	FOnHitSignature OnHit;
	
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CurrentHealth;
	
	void TakeDmg(float Dmg);
protected:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnDmgTaken
	( AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser );

	virtual void Death();
	bool bIsDead = false;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
};
