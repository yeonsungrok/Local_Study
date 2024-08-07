// Fill out your copyright notice in the Description page of Project Settings.

#include "MyStatComponent.h"

#include "MyCharacter.h"
#include "MyHpBar.h"
#include "MyGameInstance.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyStatComponent::Reset()
{
	_curHp = _maxHp;
}

void UMyStatComponent::SetLevelAndInit(int level)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (myGameInstance)
	{
		FMyStatData* data = myGameInstance->GetStatDataByLevel(level);
		_maxHp = data->maxHp;
		_attackDamage = data->attack;
		_curHp = _maxHp;

		GetOwner()->GetName();
		UE_LOG(LogTemp, Log, TEXT("%s...hp : %d, attackDamage : %d"), *GetOwner()->GetName(), _maxHp, _attackDamage);
	}
}

void UMyStatComponent::SetHp(int32 hp)
{
	// 이 함수로 curHp의 수정은 무조건 이 함수를 통해서 이루어진다.
	// 호출 될때마다 hpBar가 바뀌면 되겠다.
	_curHp = hp;

	if (_curHp <= 0)
	{
		_deathDelegate.Broadcast();
		_curHp = 0;
	}

	if (_curHp > _maxHp)
		_curHp = _maxHp;

	float ratio = HpRatio();
	_hpChangedDelegate.Broadcast(ratio);

}

int UMyStatComponent::AddCurHp(float amount)
{
	int beforHp = _curHp;
	// amount damage가 들어왔을때
	// 방어력 스탯이나, 데미지 경감 등의 옵션으로 amount가 줄어든 채로 curHp에 더해진다.
	// ex) amount *= 0.8f;

	int afterHp = beforHp + amount;
	SetHp(afterHp);

	

	return afterHp - beforHp;
}

void UMyStatComponent::AddAttackDamage(float amount)
{
	_attackDamage += amount;
}



// 데미지감소시도
void UMyStatComponent::SubAttackDamage(float amount)
{
	_attackDamage -= amount;

	if (_attackDamage < 0)
	{
		_attackDamage = 0;
	}
}

