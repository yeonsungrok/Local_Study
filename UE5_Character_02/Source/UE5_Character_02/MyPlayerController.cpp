// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

#include "MainGameMode.h"

#include "MyInvenWidget.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(_inputMappingContext, 0);
	}

	
	//// GameMode �ν��Ͻ��� ������ ���� �ν��Ͻ��� ������
	//GameModeInstance = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	//if (GameModeInstance)
	//{
	//	InvenWidget = GameModeInstance->MyInvenWidgetInstance;
	//}

}

void AMyPlayerController::ShowUI()
{
	bShowMouseCursor = true;
}

void AMyPlayerController::HideUI()
{
	bShowMouseCursor = false;
}


//// �Ʒ� ���������� ����
//void AMyPlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//	InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AMyPlayerController::ToggleInventory);
//}
//
//void AMyPlayerController::ToggleInventory()
//{
//	if (InvenWidget)
//	{
//		bool bIsVisible = InvenWidget->GetVisibility() == ESlateVisibility::Visible;
//		InvenWidget->ToggleVisibility(!bIsVisible);
//	}
//}
