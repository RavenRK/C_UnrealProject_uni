// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasePawn.h"

#include "Components/BoxComponent.h"
//#include "Components/BoxComponent.h"

AMyBasePawn::AMyBasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColl"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	SetRootComponent(BoxComponent);
	BaseMesh->SetupAttachment(BoxComponent);
	TurretMesh->SetupAttachment(BaseMesh);
}


