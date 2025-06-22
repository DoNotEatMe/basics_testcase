// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BTTask_FireAtPlayer.h"

#include "AIController.h"
#include "Enemy/BasicEnemy.h"
#include "Enemy/EnemyProjectile.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FireAtPlayer::UBTTask_FireAtPlayer()
{
	NodeName = "Fire At Player";
}

EBTNodeResult::Type UBTTask_FireAtPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ABasicEnemy* Monster = Cast<ABasicEnemy>(AIController->GetPawn());
	if (!Monster || !Monster->ProjectileClass) return EBTNodeResult::Failed;

	AActor* Player = UGameplayStatics::GetPlayerPawn(Monster, 0);
	if (!Player) return EBTNodeResult::Failed;

	const FVector MuzzleLocation = Monster->GetActorLocation() + Monster->GetActorForwardVector() * 100.f;
	const FRotator MuzzleRotation = (Player->GetActorLocation() - MuzzleLocation).Rotation();

	FActorSpawnParameters Params;
	Params.Owner = Monster;
	Params.Instigator = Monster;

	AActor* Projectile = Monster->GetWorld()->SpawnActor<AActor>(
		Monster->ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

	return Projectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}