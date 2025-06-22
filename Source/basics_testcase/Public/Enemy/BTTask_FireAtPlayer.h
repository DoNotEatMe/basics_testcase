// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FireAtPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BASICS_TESTCASE_API UBTTask_FireAtPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FireAtPlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
