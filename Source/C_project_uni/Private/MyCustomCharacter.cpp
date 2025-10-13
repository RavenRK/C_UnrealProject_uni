// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCustomCharacter.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AMyCustomCharacter::AMyCustomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComponent;	// make capsule collider & set as root

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	MeshComponent->SetupAttachment(RootComponent); //make base mesh & attach it to root

	
}

void AMyCustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

