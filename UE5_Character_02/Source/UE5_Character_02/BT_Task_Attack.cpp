// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_Attack.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"
#include "MyCharacter.h"
#include "MyMonsters.h"
#include "MyPlayer.h"

UBT_Task_Attack::UBT_Task_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBT_Task_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto character = Cast <AMyMonsters>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return EBTNodeResult::Failed;

	character->Attack_AI();
	_isAttacking = true;
	
	character->_attackEndedDelegate.AddLambda(
	[this]()-> void 
	{
		this->_isAttacking = false;
	});
		

	return result;
}

void UBT_Task_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);


	// 몬스터 방향하려면 Tick에다가 넣어야함. (현재 BB안에 노드로 사용함)


}
