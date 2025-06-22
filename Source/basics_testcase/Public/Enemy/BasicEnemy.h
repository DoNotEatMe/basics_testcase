// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasicEnemy.generated.h"

class AEnemyProjectile;
class UBehaviorTree;
class UFloatingPawnMovement;
class ASpawnPoint;

UCLASS()
class BASICS_TESTCASE_API ABasicEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicEnemy();

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CurrentHP = 0;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxHP = 100;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float EXPOnDeath = 40;

	void SetSpawner(ASpawnPoint* SpawnActor);

	void Revive();

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AEnemyProjectile> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* MovementComponent;

	virtual float TakeDamage(
		float DamageAmount,
		FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;

	

	void Die(AController* EventInstigator);

	UPROPERTY()
	TWeakObjectPtr<ASpawnPoint> Spawner;





	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
