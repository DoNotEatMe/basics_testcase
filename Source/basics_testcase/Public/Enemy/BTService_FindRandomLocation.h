// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class BASICS_TESTCASE_API UBTService_FindRandomLocation : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_FindRandomLocation();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float SearchRadius = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetLocationKey;
	
};
