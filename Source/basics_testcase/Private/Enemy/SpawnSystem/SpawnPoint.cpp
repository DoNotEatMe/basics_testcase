#include "Enemy/SpawnSystem/SpawnPoint.h"
#include "Enemy/BasicEnemy.h"
#include "GameFramework/MonsterSubsystem.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnPointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnPointBox;
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	Pool = GetWorld()->GetSubsystem<UMonsterSubsystem>();
	if (!ensure(Pool)) return;
	for (int32 i = 0; i < MaxActiveMonsters; ++i)
	{
		TrySpawn();
	}
}

void ASpawnPoint::TrySpawn()
{
	if (!ensure(Pool && MonsterClass)) return;

	const FVector SpawnLocation = GetRandomPointInBounds();
	ABasicEnemy* Monster = Pool->RequestMonster(SpawnLocation, MonsterClass);
	if (Monster)
	{
		Monster->SetSpawner(this);
	}
}

FVector ASpawnPoint::GetRandomPointInBounds()
{
	if (!SpawnPointBox)
	{
		return GetActorLocation();
	}

	const FVector Origin = SpawnPointBox->Bounds.Origin;
	const FVector Extent = SpawnPointBox->GetScaledBoxExtent();

	const float RandX = FMath::FRandRange(-Extent.X, Extent.X);
	const float RandY = FMath::FRandRange(-Extent.Y, Extent.Y);

	return Origin + FVector(RandX, RandY, GetActorLocation().Z);
}


void ASpawnPoint::NotifyMonsterDied(ABasicEnemy* DeadEnemy)
{
	if (!ensure(Pool && DeadEnemy)) return;

	Pool->ReturnMonsterToPool(DeadEnemy);

	FTimerHandle RespawnTimer;
	GetWorldTimerManager().SetTimer(
		RespawnTimer,
		this,
		&ASpawnPoint::TrySpawn,
		RespawnDelay,
		false
	);
}

