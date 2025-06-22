// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurnToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BASICS_TESTCASE_API UBTTask_TurnToPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_TurnToPlayer();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	TWeakObjectPtr<APawn> CachedPawn;
	FRotator StartRotation;
	FRotator TargetRotation;
	float ElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float TurnDuration = 0.3f;
};
