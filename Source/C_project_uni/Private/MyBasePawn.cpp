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

void AMyBasePawn::RoateTO(FVector Target)
{
	FVector VectorToTarget = Target - TurretMesh->GetComponentLocation();

	FRotator LookAtRotation = FRotator(0, VectorToTarget.Rotation().Yaw,0);
	LookAtRotation += FRotator(0,90,0);

	FRotator InterpolatedRotation = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		GetWorld()->GetDeltaSeconds(),
		10);
	
	TurretMesh->SetWorldRotation(InterpolatedRotation);
}



