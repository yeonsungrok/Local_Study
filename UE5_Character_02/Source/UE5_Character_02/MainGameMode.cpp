// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "GameFramework/Pawn.h"

#include "MyCharacter.h"
//������ ���� �߰� ��Ŭ���..3����.
#include "Engine/World.h"
#include "MyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Blueprint/UserWidget.h"

AMainGameMode::AMainGameMode()
//: bIsInventoryVisible(false) // ���������� �߰�.
{
	//// ���� �������Ʈ Ŭ������ ã��
	//static ConstructorHelpers::FClassFinder<UMyInvenWidget> InvenWidgetBPClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/MyInven_BP.MyInven_BP_C'"));
	//if (InvenWidgetBPClass.Succeeded())
	//{
	//	MyInvenWidgetClass = InvenWidgetBPClass.Class;
	//}



	static ConstructorHelpers::FClassFinder<AMyCharacter>
	myCharacter(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Players/MyCharacter_BP.MyCharacter_BP_C'"));

	if(myCharacter.Succeeded())
	{
		DefaultPawnClass = myCharacter.Class;
	}

	static ConstructorHelpers::FClassFinder<AMyCharacter>
		myMonster(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Players/MyMonster_BP.MyMonster_BP_C'"));
	if (myMonster.Succeeded())
	{
		_monsterClass = myMonster.Class;
	}

}

void AMainGameMode::BeginPlay()
{
	//// ĳ������ ��ġ ��������.
	//FVector centerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	//float radius = 600.0f;

	//// ���� ����
	//int monsterCount = 10;
	//float angleIncrement = 360.0f / monsterCount;


	// ĳ���� �αٿ�.. ã�Ƽ� ������ �ֵ���
	// ��ġ��...
	FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() + FVector(600,0.0f,0.0f);
	FRotator rotator = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();
	// ���赵�� �־������. 


	//TODO : MyMonster.cpp �����ؾ���
	
	// SPawn ����..
	//for (int i = 0; i < 8; i++)
	//{
	//	location.X += 100.0 * i;
	//	rotator.Yaw += 60.0 * i;

	//	AMyCharacter* SpawnedActor = GetWorld()->SpawnActor<AMyCharacter>(_monsterClass, location, rotator);
	//////SpawnedActor->AIControllerClass = AMyAIController::StaticClass();
	//	SpawnedActor->SetActorLocation(location);

	//	_monsters.Add(SpawnedActor); // ���͵��� ������ ���� �Ҵ��ؼ� ��ġ.
	//}
	

	//// �κ� ������ ���Ѱ�
	//if (MyInvenWidgetClass)
	//{
	//	MyInvenWidgetInstance = CreateWidget<UMyInvenWidget>(GetWorld(), MyInvenWidgetClass);
	//	if (MyInvenWidgetInstance)
	//	{
	//		MyInvenWidgetInstance->AddToViewport();
	//		MyInvenWidgetInstance->ToggleVisibility(false); // �ʱ⿡�� ����
	//	}
	//}


}



