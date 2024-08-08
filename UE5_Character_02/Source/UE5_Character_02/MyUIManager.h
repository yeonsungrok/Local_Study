// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyUIManager.generated.h"

class UMyInvenWidget;

UCLASS()
class UE5_CHARACTER_02_API AMyUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UMyInvenWidget* GetInvenUI() { return _invenWidget; }

private:
	// // UI �κ� ���� (������Ʈ�� �ƴ϶� �״�� �ҷ���)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	UMyInvenWidget* _invenWidget;

};
