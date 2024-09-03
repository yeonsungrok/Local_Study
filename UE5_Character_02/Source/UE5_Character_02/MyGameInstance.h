// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"
#include "MyStatComponent.h"

#include "MyGameInstance.generated.h"
/**
 * 
 */
class AMyUIManager;
class AMyEffectManager;

class AMySoundManager;

#define UIManager Cast<UMyGameInstance>(GetGameInstance())->GetUIManager()
#define EffectManager Cast<UMyGameInstance>(GetGameInstance())->GetEffectManager()

#define SoundManager Cast<UMyGameInstance>(GetGameInstance())->GetSoundManager()

UCLASS()


class UE5_CHARACTER_02_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;

	FMyStatData* GetStatDataByLevel(int level);

	AMyUIManager* GetUIManager() { return _uiManager; }
	AMyEffectManager* GetEffectManager() { return _effectManager; }
	AMySoundManager* GetSoundManager() { return _soundManager; }

private:
	UPROPERTY()
	class UDataTable* _statTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AMyUIManager* _uiManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AMyEffectManager* _effectManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AMySoundManager* _soundManager;


};
