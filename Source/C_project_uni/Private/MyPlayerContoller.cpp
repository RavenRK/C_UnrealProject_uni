// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerContoller.h"
#include "PlayerTank.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "PickUpBase.h"
#include "ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

void AMyPlayerContoller::BeginPlay()
{
	Super::BeginPlay();
	PlayerWeaponChnage(StoredProjectileType);
}

void AMyPlayerContoller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	PlayerTank->RotateTo(HitResult.ImpactPoint);

}

void AMyPlayerContoller::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	InputSubsystem->AddMappingContext(MappingContext, 0);
}

void AMyPlayerContoller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerTank = Cast<APlayerTank>(InPawn);
	
	bShowMouseCursor = true; // show Cursor

	if (MoveAction && AttackAction && RotateAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this,&AMyPlayerContoller::HandleMove);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed,this,&AMyPlayerContoller::MoveCompleted);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered,this,&AMyPlayerContoller::HandleRotate);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this,&AMyPlayerContoller::HandleAttack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this,&AMyPlayerContoller::EndAttackTimer);
		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Completed, this,&AMyPlayerContoller::PickUp);
	}
}

void AMyPlayerContoller::HandleMove(const FInputActionValue& IAValue)
{
	if (!PlayerTank->bisAlive) {return;}

	PlayerTank->PlayerMoveFeedBack();
	
	float Value = IAValue.Get<float>();
	FVector DeltaLocation = FVector(0,0,0);
	DeltaLocation.X = PlayerTank->MoveSpeed * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	PlayerTank->AddActorLocalOffset(DeltaLocation, true);
	
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, TEXT("move"));
}
void AMyPlayerContoller::MoveCompleted()
{
	PlayerTank->PlayerStopMoveFeedBack();
}

void AMyPlayerContoller::HandleRotate(const FInputActionValue& IAValue)
{
	if (!PlayerTank->bisAlive) {return;}
	float Value = IAValue.Get<float>();
	FRotator DeltaRotation = FRotator(0,0,0);
	DeltaRotation.Yaw =  PlayerTank->RotateSpeed * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	PlayerTank->AddActorLocalRotation(DeltaRotation, true);
	
	//GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Green, TEXT("HandleRotate"));
}

void AMyPlayerContoller::HandleAttack()
{
	if (!PlayerTank->bisAlive) {return;}
	if (GetWorldTimerManager().IsTimerActive(AttackSpeedTimer))
		return;

	if (bCanAttack)
	{
		Attack();
		bCanAttack = false;
	}
	
	GetWorldTimerManager().SetTimer(FirstShotCDTimer, this,
		&AMyPlayerContoller::FirstShotCD,  PlayerTank->AttackSpeed, false);
	
	GetWorldTimerManager().SetTimer(AttackSpeedTimer, this,
		&AMyPlayerContoller::Attack,  PlayerTank->AttackSpeed, true);
	
	//GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Green, TEXT("attack"));
}
void AMyPlayerContoller::EndAttackTimer()
{	GetWorld()->GetTimerManager().ClearTimer(AttackSpeedTimer);	}

void AMyPlayerContoller::PickUp()
{
	PlayerTank->PickUpRange->GetOverlappingActors(Overlaps,APickUpBase::StaticClass());
	for (AActor* Actor : Overlaps)
	{
		if (APickUpBase* Pickup = Cast<APickUpBase>(Actor))
		{
			TSubclassOf<AProjectileBase> LastProJRef = PlayerTank->ProJBase;
			PlayerTank->ProJBase = Pickup->ProJRef;
			Pickup->ChangePickUps(LastProJRef);

			PlayerWeaponChnage(StoredProjectileType);
		}
	}
}

void AMyPlayerContoller::PlayerWeaponChnage(EMyEnum ProjectileType)
{
	ProjectileType = Cast<AProjectileBase>(PlayerTank->ProJBase->GetDefaultObject())->ProjectileType;
	PlayerTank->WeaponStatChange(ProjectileType);
}

void AMyPlayerContoller::FirstShotCD()	{bCanAttack = true; }
void AMyPlayerContoller::Attack()
{
	//maybe some got other stuff to add 
	PlayerTank->Fire(PlayerTank->DmgMultiplier);
}



