// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

enum class EMyEnum : uint8;
class AProjectileBase;
class USphereComponent;
class UNavigationSystemBase;

UCLASS()
class C_PROJECT_UNI_API APickUpBase : public AActor
{
	GENERATED_BODY()

public:
	APickUpBase();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly , Category = "Pickup")
	TSubclassOf<AProjectileBase> ProJRef;
	
	UPROPERTY()
	AProjectileBase* ProJClassRef;
	
	UFUNCTION(BlueprintNativeEvent)
	void ChangeVFX(EMyEnum ProJType);
	
	void ChangePickUps(TSubclassOf<AProjectileBase> NewProJRef);

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	USphereComponent* CollisionSphere;
	
	UPROPERTY()
	EMyEnum StoredProjectileType;
};
