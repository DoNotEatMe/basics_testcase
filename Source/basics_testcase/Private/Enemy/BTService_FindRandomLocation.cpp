// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BTService_FindRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_FindRandomLocation::UBTService_FindRandomLocation()
{
	bNotifyBecomeRelevant = true;
	bNotifyTick = false;
	NodeName = "Find Random Location";

	TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_FindRandomLocation, TargetLocationKey));
}

void UBTService_FindRandomLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!ensure(AIController)) return;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ensure(ControlledPawn)) return;

	UWorld* World = ControlledPawn->GetWorld();
	if (!ensure(World)) return;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if (!ensure(NavSys)) return;

	FNavLocation Result;
	if (NavSys->GetRandomReachablePointInRadius(ControlledPawn->GetActorLocation(), SearchRadius, Result))
	{
		if (UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent())
		{
			BB->SetValueAsVector(TargetLocationKey.SelectedKeyName, Result.Location);
		}
	}
}