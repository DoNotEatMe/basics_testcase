// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BasicEnemy.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	CurrentHP = MaxHP;
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

	if (ActualDamage <= 0.f || bIsDead)
	{
		return 0.f;
	}

	CurrentHP -= ActualDamage;

	UE_LOG(LogTemp, Warning, TEXT("Enemy took %.2f damage from %s"), DamageAmount,
	       *DamageCauser->GetName());

	if (CurrentHP <= 0.f)
	{
		Die();
	}

	return ActualDamage;
}

void ABasicEnemy::Die()
{
	bIsDead = true;
	this->Destroy();
}


// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasicEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
