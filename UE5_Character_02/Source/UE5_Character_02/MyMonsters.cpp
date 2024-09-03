// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMonsters.h"

#include "MyGameInstance.h"

#include "MyAIController.h"
#include "MyAnimInstance.h"
#include "Kismet/GameplayStatics.h"

#include "MySoundManager.h"


AMyMonsters::AMyMonsters()
{
}

void AMyMonsters::BeginPlay()
{
	Super::BeginPlay();

	_aiController = Cast<AAIController>(GetController());

}



void AMyMonsters::Attack_AI()
{
	if (_statCom->IsDead())
		return;

	if (_isAttacking == false && _animInstance != nullptr)
	{

		_animInstance->PlayAttackMontage();
		_isAttacking = true;


		_curAttackIndex %= 4;
		_curAttackIndex++;

		_animInstance->JumpToSection(_curAttackIndex);
		
	}
}


void AMyMonsters::PlayAttackHitSound(FString SoundName, FVector location)
{
	Super::PlayAttackHitSound(SoundName, location);

	/*UGameplayStatics::execSpawnSoundAtLocation();*/
	if(SoundManager)
	{
		SoundManager->PlaySound("MonsterDamageCue", location);
	}

}

void AMyMonsters::AttackHit()
{
	Super::AttackHit();

}


