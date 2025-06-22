// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MonsterSubsystem.generated.h"

class ABasicEnemy;
/**
 * 
 */
UCLASS()
class BASICS_TESTCASE_API UMonsterSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	ABasicEnemy* RequestMonster(const FVector& SpawnLocation, TSubclassOf<ABasicEnemy> MonsterClass);
	void ReturnMonsterToPool(ABasicEnemy* Monster);

protected:
	UPROPERTY(EditAnywhere)
	int32 InitialPoolSize = 10;

	UPROPERTY(EditAnywhere)
	int32 MaxPoolSize = 100;
	
	TArray<ABasicEnemy*> Pool;
	
	TSet<ABasicEnemy*> ActiveMonsters;

	ABasicEnemy* CreateMonster(TSubclassOf<ABasicEnemy> MonsterClass);

};
