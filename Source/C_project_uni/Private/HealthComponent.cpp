// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	maxHP = currentHP;
	
}


void UHealthComponent::TakeDmg(float DmgAmount, float& Current_HP)
{
	
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

