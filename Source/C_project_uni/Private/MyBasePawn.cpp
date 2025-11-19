// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasePawn.h"
#include "Components/BoxComponent.h"

AMyBasePawn::AMyBasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColl"));
	SetRootComponent(BoxComponent);
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(BoxComponent);
	
	TurrentMeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TurrentRoot"));
	TurrentMeshRoot->SetupAttachment(BaseMesh);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(TurrentMeshRoot);
	
	ProJSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProJSpawnPoint"));
	ProJSpawnPoint->SetupAttachment(TurretMesh);
}

void AMyBasePawn::RotateTo(FVector Target)
{
	FVector VectorToTarget = Target - TurretMesh->GetComponentLocation();

	FRotator LookAtRotation = FRotator(0, VectorToTarget.Rotation().Yaw,0);

	FRotator InterpolatedRotation = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		GetWorld()->GetDeltaSeconds(),
		10);
	
	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

void AMyBasePawn::Fire()
{
	FVector SpawnLocation = ProJSpawnPoint->GetComponentLocation();
	FRotator SPawnRoation = ProJSpawnPoint->GetComponentRotation();

	DrawDebugSphere(GetWorld(), SpawnLocation,25, 12, FColor::Red, false, 2);
}



