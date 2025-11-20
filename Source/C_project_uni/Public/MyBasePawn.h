// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyBasePawn.generated.h"

class UHealthComp;
class UBoxComponent;
class AProjectileBase;

UCLASS(Abstract)
class C_PROJECT_UNI_API AMyBasePawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* TurrentMeshRoot;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* ProJSpawnPoint;
	
	UPROPERTY(EditAnywhere)
	UHealthComp* HealthCompo;
	
	virtual void RotateTo(FVector Target);
	virtual void Fire();

protected:
	AMyBasePawn();
	
	//Tsubclassof cuz we cant accsess the Bp in here
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileBase> ProJBase;

	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

	
};
