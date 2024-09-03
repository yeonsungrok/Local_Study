// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "MyUIManager.h"
#include "MyEffectManager.h"
#include "MySoundManager.h"

UMyGameInstance::UMyGameInstance()
{
	//�����ڿ��� �𸮾󿡼� ���� �����͸� ����;��Ѵ�. ��) level
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable
	(TEXT("/Script/Engine.DataTable'/Game/Data/MyStatDataTable.MyStatDataTable'"));

	if (dataTable.Succeeded())
	{
		_statTable = dataTable.Object;
		UE_LOG(LogTemp, Error, TEXT("StatTable Load Complete"));
	}

	


}

void UMyGameInstance::Init()
{
	Super::Init();

	auto statData = GetStatDataByLevel(2);
	UE_LOG(LogTemp, Warning, TEXT("Level : %d, MaxHp : %d, Attack : %d ")
	, statData->level, statData->maxHp, statData->attack);

	FActorSpawnParameters params;
	params.Name = TEXT("UIManager"); // �𸮾� �����Ϳ��� ���̴� �̸�
	_uiManager = GetWorld()->SpawnActor<AMyUIManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	// EffectManager
	params.Name = TEXT("EffectManager");
	_effectManager = GetWorld()->SpawnActor<AMyEffectManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	// SoundManager
	params.Name = TEXT("SoundManager");
	_soundManager = GetWorld()->SpawnActor<AMySoundManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	

}

FMyStatData* UMyGameInstance::GetStatDataByLevel(int level)
{
	auto statData = _statTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT("")); // int�� string���� �����

	return statData;
}
