#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

class UMonsterSubsystem;
class ABasicEnemy;
class UBoxComponent;

UCLASS()
class BASICS_TESTCASE_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnPoint();

	void NotifyMonsterDied(ABasicEnemy* DeadEnemy);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float RespawnDelay = 5.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABasicEnemy> MonsterClass;

	UPROPERTY(EditAnywhere)
	int32 MaxActiveMonsters = 10;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SpawnPointBox;

	void TrySpawn();
	
	UPROPERTY(Transient)
	UMonsterSubsystem* Pool = nullptr;

	FVector GetRandomPointInBounds();
};
