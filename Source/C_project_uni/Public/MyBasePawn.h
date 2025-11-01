// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyBasePawn.generated.h"

class UCapsuleComponent;
class UBoxComponent;
UCLASS()
class C_PROJECT_UNI_API AMyBasePawn : public APawn
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

protected:
	AMyBasePawn();
};
