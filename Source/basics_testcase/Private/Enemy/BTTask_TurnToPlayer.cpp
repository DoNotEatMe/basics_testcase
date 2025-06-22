// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BTTask_TurnToPlayer.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTTask_TurnToPlayer::UBTTask_TurnToPlayer()
{
	NodeName = "Turn To Player";
	bNotifyTick = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_TurnToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;

	AActor* Player = UGameplayStatics::GetPlayerPawn(AIPawn, 0);
	if (!Player) return EBTNodeResult::Failed;

	FVector ToPlayer = (Player->GetActorLocation() - AIPawn->GetActorLocation()).GetSafeNormal();
	TargetRotation = ToPlayer.Rotation();
	TargetRotation.Pitch = 0;
	TargetRotation.Roll = 0;

	StartRotation = AIPawn->GetActorRotation();
	StartRotation.Pitch = 0;
	StartRotation.Roll = 0;

	CachedPawn = AIPawn;
	ElapsedTime = 0.0f;

	return EBTNodeResult::InProgress;
}


void UBTTask_TurnToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!CachedPawn.IsValid())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	ElapsedTime += DeltaSeconds;
	float Alpha = FMath::Clamp(ElapsedTime / TurnDuration, 0.f, 1.f);

	FRotator NewRotation = FMath::Lerp(StartRotation, TargetRotation, Alpha);
	CachedPawn->SetActorRotation(NewRotation);

	if (Alpha >= 1.f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

