// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffect.h"

#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AMyEffect::AMyEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Actor => SpawnWorld를 무조건 써야한다.. 월드에 배치하려고하기때문에..
	// Component => CreateDefaultSubObject 가 동적할당을 하는 역할
	// UObeject => NewObject<T>  잘쓰지는 않는다.. (프로그래머가 직접 지워줘야하기때문)

	_particleCom = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = _particleCom;
	//_particleCom->SetupAttachment(RootComponent);   // 위나 아랫것중 하나

	_niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	_niagaraCom->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyEffect::BeginPlay()
{
	Super::BeginPlay();
	
	_particleCom->OnSystemFinished.AddDynamic(this, &AMyEffect::End); //One Play and Stop
	End(_particleCom);

	_niagaraCom->OnSystemFinished.AddDynamic(this, &AMyEffect::EndNiagara);
	EndNiagara(_niagaraCom);

}

// Called every frame
void AMyEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffect::Play(FVector location, FRotator rotator)
{
	if (_particleCom->IsActive() || _niagaraCom->IsActive())
		return;


	SetActorLocationAndRotation(location, rotator);
	_particleCom->ActivateSystem();
	_niagaraCom->ActivateSystem();
}

bool AMyEffect::IsPlaying()
{
	if (_particleCom->IsActive())
		return true;

	if (_niagaraCom->IsActive())
		return true;


	return false;
}

void AMyEffect::End(UParticleSystemComponent* particle)
{
	if(particle)
		particle->DeactivateSystem();
	// Arrow도 컴포넌트 추가해서 가능함.

}

void AMyEffect::EndNiagara(UNiagaraComponent* particle)
{
	if (particle)
		particle->Deactivate();
}

