// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/MonsterSubsystem.h"

#include "Enemy/BasicEnemy.h"


void UMonsterSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UMonsterSubsystem::Deinitialize()
{
    for (auto& Monster : Pool)
    {
        if (Monster) Monster->Destroy();
    }

    Pool.Empty();
    ActiveMonsters.Empty();
}

ABasicEnemy* UMonsterSubsystem::RequestMonster(const FVector& SpawnLocation, TSubclassOf<ABasicEnemy> MonsterClass)
{

    for (ABasicEnemy* Monster : Pool)
    {
        if (!ActiveMonsters.Contains(Monster))
        {
            Monster->SetActorLocation(SpawnLocation);
            Monster->SetActorHiddenInGame(false);
            Monster->SetActorEnableCollision(true);
            Monster->SetActorTickEnabled(true);
            Monster->Revive();

            ActiveMonsters.Add(Monster);
            return Monster;
        }
    }

    if (Pool.Num() < MaxPoolSize)
    {
        ABasicEnemy* NewMonster = CreateMonster(MonsterClass);
        if (NewMonster)
        {
            Pool.Add(NewMonster);
            NewMonster->SetActorLocation(SpawnLocation);
            NewMonster->SetActorHiddenInGame(false);
            NewMonster->SetActorEnableCollision(true);
            NewMonster->SetActorTickEnabled(true);

            ActiveMonsters.Add(NewMonster);
            return NewMonster;
        }
    }

    return nullptr;
}

void UMonsterSubsystem::ReturnMonsterToPool(ABasicEnemy* Monster)
{
    if (!ensure(Monster)) return;

    Monster->SetActorHiddenInGame(true);
    Monster->SetActorEnableCollision(false);
    Monster->SetActorTickEnabled(false);
    Monster->SetSpawner(nullptr);
    ActiveMonsters.Remove(Monster);
}

ABasicEnemy* UMonsterSubsystem::CreateMonster(TSubclassOf<ABasicEnemy> MonsterClass)
{
    UWorld* World = GetWorld();
    if (!ensure(World)) return nullptr;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    return World->SpawnActor<ABasicEnemy>(MonsterClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
}
