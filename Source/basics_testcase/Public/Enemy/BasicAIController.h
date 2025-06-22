// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class BASICS_TESTCASE_API ABasicAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABasicAIController();
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;
};
