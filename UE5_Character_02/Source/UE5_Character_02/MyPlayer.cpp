// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

#include "MyGameInstance.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/SpringArmComponent.h"

// TPS
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Input
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// animation
#include "MyAnimInstance.h"

// particle
#include "MyEffectManager.h"
#include "Kismet/GameplayStatics.h"

// Sound
#include "MySoundManager.h"


////particle
#include "MyEffectManager.h"

AMyPlayer::AMyPlayer()
{

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// ��Ӱ���
	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 550.0f;
	_springArm->SetRelativeRotation(FRotator(-17.0f, 0.0f, 0.0f));

	// ������
	SetActorScale3D(FVector(1.2f, 1.2f, 1.2f));

}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();


}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);

		// Looking
		EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);

		// JumpA
		EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Started, this, &AMyPlayer::JumpA);

		// ����
		EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &AMyPlayer::AttackA);

		// GŰ ���
		EnhancedInputComponent->BindAction(_dropAction, ETriggerEvent::Started, this, &AMyPlayer::DropItemFromCharacter);
	}
}

void AMyPlayer::AttackHit()
{
	/*Super::AttackHit();*/

	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this); //this �ڱ��ڽ��� �����϶�.. ���� ������ ���������ü�����..


	float attackRange = 1000.0f;
	float virtualAttackRange = 100000.0f;
	float attackRadius = 20.0f;

	FVector forward = _camera->GetForwardVector(); // 회전값의 방향
	FQuat quat = FQuat::FindBetweenVectors(FVector(0, 0, 1), forward);

	//UE_LOG(LogTemp, Log, TEXT("%s"), *vec.ToString());
	FVector start = _camera->GetComponentLocation();
	FVector end = start + forward * (virtualAttackRange * 0.5f);
	FVector center = (start + end) * 0.5f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		start,
		end,
		quat,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(attackRadius, virtualAttackRange * 0.5f),

		params
	);

	FColor drawColor = FColor::Green;

	bool check = false;
	auto victim = hitResult.GetActor(); // 맞은놈
	if (victim)
	{
		FVector victimLocation = victim->GetActorLocation();
		FVector myLocation = GetActorLocation();

		check = FVector::Distance(myLocation, victimLocation) < attackRange;
	}
	


	if (bResult && hitResult.GetActor()->IsValidLowLevel() && check)
	{
		
		drawColor = FColor::Red;
		FDamageEvent damageEvent;
		hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamge(), damageEvent, GetController(), this);
		_hitPoint = hitResult.ImpactPoint;

		
		EffectManager->Play("Particle", _hitPoint);

		PlayAttackHitSound("DefaultSound", _hitPoint);
	}

	//DrawDebugCapsule(GetWorld(), center, virtualAttackRange * 0.5f, attackRadius, quat, drawColor, false, 2.0f);
	DrawDebugLine(GetWorld(), start, end, drawColor, false, 2.0f);

}

void AMyPlayer::PlayAttackHitSound(FString SoundName, FVector location)
{
	Super::PlayAttackHitSound(SoundName, location);


	if (SoundManager)
	{
		SoundManager->PlaySound("MonsterDamageCue", location);
	}

}





void AMyPlayer::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		_vertical = MovementVector.Y;
		_horizontal = MovementVector.X;

		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);

	}
}

void AMyPlayer::Look(const FInputActionValue& value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void AMyPlayer::JumpA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		////�׽�Ʈ �α� ���
		//UE_LOG(LogTemp, Warning, TEXT("Jump!!"));

		ACharacter::Jump();
	}
}

void AMyPlayer::AttackA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();
	if (isPressed && _isAttacking == false && _animInstance != nullptr)
	{

		_animInstance->PlayAttackMontage();
		_isAttacking = true;


		_curAttackIndex %= 4;
		_curAttackIndex++;

		_animInstance->JumpToSection(_curAttackIndex);



	}
}

