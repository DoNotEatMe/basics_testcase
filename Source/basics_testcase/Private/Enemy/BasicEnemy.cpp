// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BasicEnemy.h"

#include "Character/CharacterStatsComponent.h"
#include "Enemy/BasicAIController.h"
#include "Enemy/SpawnSystem/SpawnPoint.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	
	AIControllerClass = ABasicAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	Revive();

}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
}

float ABasicEnemy::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	const float ActualDamage = FMath::Max(0.f, DamageAmount);

	if (ActualDamage <= 0.f)
	{
		return 0.f;
	}

	CurrentHP -= ActualDamage;

	UE_LOG(LogTemp, Warning, TEXT("Enemy took %.2f damage from %s"), DamageAmount,
	       *DamageCauser->GetName());

	if (CurrentHP <= 0.f)
	{
		Die(EventInstigator);
	}

	return ActualDamage;
}

void ABasicEnemy::Die(AController* EventInstigator)
{
	APawn* PlayerPawn = EventInstigator->GetPawn();
	if (UCharacterStatsComponent* Stats = PlayerPawn->FindComponentByClass<UCharacterStatsComponent>(); PlayerPawn && Stats)
	{
		Stats->GainEXP(EXPOnDeath);
	}
	if (Spawner.IsValid())
	{
		Spawner->NotifyMonsterDied(this);
	}
}

void ABasicEnemy::SetSpawner(ASpawnPoint* SpawnActor)
{
	if (SpawnActor){
		Spawner = SpawnActor;
	}
}

void ABasicEnemy::Revive()
{
	CurrentHP = MaxHP;
}


// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UPawnMovementComponent* ABasicEnemy::GetMovementComponent() const
{
	return MovementComponent;
}
