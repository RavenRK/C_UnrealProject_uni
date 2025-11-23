// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodeAOE.h"


AExplodeAOE::AExplodeAOE()
{
}

void AExplodeAOE::BeginPlay()
{
	Super::BeginPlay();
	//get tsubclassof myBasePawn and Call on Dmg to all of them
	//maybe get status effect and see call elec effect
	AOEFeedBack();
}

void AExplodeAOE::AOEFeedBack_Implementation()
{
	//spawn VFX
}
