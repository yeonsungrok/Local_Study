// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/BluePrint/AI/MonsterBB_BP.MonsterBB_BP'"));
	if (BB.Succeeded())
	{
		_bb = BB.Object; 
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/MonsterBT_BP.MonsterBT_BP'"));
	if (BT.Succeeded())
	{
		_bt = BT.Object;
	}
}
// Possess  :  ��Ʈ�ѷ��� ���� �����ϴ� ��
void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// RandMove�� 3.0f �� 3�ʸ��� �����Ǵ� ��.
	// GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &AMyAIController::RandMove, 3.0f, true);

	UBlackboardComponent* bloackBoardComponent = Blackboard;
	if (UseBlackboard(_bb, bloackBoardComponent))
	{
		if (RunBehaviorTree(_bt))
		{
			bloackBoardComponent->SetValueAsVector(FName("FixedPos"), InPawn->GetActorLocation());
			UE_LOG(LogTemp, Log, TEXT("Behavior Tree Succeeded"));
		}
	}


}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	// GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void AMyAIController::RandMove()
{
	auto currentPawn = GetPawn();

	if (!currentPawn->IsValidLowLevel())
		return;
	

	auto naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (naviSystem == nullptr)
		return;

	FNavLocation randLocation;

	// AI�� �ڵ� �����̵��� (Nav Mesh Bounce Voulume�� �𸮾󿡼� ��Ƶΰ� ��)
	if (naviSystem->GetRandomPointInNavigableRadius(currentPawn->GetActorLocation(), 500.0f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation);
	
	}
	
	
}
