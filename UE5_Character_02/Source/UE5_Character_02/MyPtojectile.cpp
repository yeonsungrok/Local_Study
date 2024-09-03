// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPtojectile.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyPtojectile::AMyPtojectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	
	_collider->InitCapsuleSize(100, 100);

	_meshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	

	_movementCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMove"));

	RootComponent = _meshCom;
	_collider->SetupAttachment(_meshCom);
}

// Called when the game starts or when spawned
void AMyPtojectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPtojectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator curRotation = GetActorRotation();

	//curRotation.Yaw += DeltaTime * 100.0f;
	curRotation.Pitch += DeltaTime * 100.0f;

	SetActorRotation(curRotation);
}

void AMyPtojectile::FireInDirection(const FVector& ShootDirection)
{
	_movementCom->Velocity = ShootDirection * _movementCom->InitialSpeed;

}

