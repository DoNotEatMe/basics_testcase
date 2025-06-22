// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BasicAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/BasicEnemy.h"

class UNavigationSystemV1;

ABasicAIController::ABasicAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void ABasicAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABasicEnemy* Monster = Cast<ABasicEnemy>(InPawn);
	if (Monster && Monster->BehaviorTree)
	{
		UseBlackboard(Monster->BehaviorTree->BlackboardAsset, BlackboardComp);
		RunBehaviorTree(Monster->BehaviorTree);
	}
}

