// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UCapsuleComponent;
class UProjectileMovementComponent; 

UCLASS()
class C_PROJECT_UNI_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AProjectileBase();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "ProJStats")
	float ProJDmg = 25;
	UPROPERTY(EditDefaultsOnly, Category = "ProJStats")
	float StartSpeed = 2500;
	UPROPERTY(EditDefaultsOnly, Category = "ProJStats")
	float MaxSpeed = 2600;
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit );

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProJRoot;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjMoveComp;
	
};
