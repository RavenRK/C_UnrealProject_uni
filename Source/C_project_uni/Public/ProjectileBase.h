// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UBoxComponent;
class UProjectileMovementComponent; 

UCLASS()
class C_PROJECT_UNI_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AProjectileBase();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "ProJStats")
	float ProJDmg = 25;
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit );

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void OnHitFeedBack();
	

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BaseColl;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProJRoot;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjMoveComp;
	
};
