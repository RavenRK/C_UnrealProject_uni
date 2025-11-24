// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyBasePawn.generated.h"

class UStatusEffects;
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
	
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Stats | Attack")
	float ProJSpreadAngle = 6;
	
	virtual void RotateTo(FVector Target);
	virtual void Fire(float Dmg); 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats | Attack")
	float DmgMultiplier = 15;
	
	UFUNCTION()
	virtual void OnPawnDestruction(AActor* DeadActor);
	
	UFUNCTION(BlueprintNativeEvent)
	void DeathFeedBack();
	
	//Tsubclassof cuz bp
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Stats | Attack")
	TSubclassOf<AProjectileBase> ProJBase;
protected:
	AMyBasePawn();
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* TurretMesh;
	
	
};
