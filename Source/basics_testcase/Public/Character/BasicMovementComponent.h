// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicMovementComponent.generated.h"

class APawn;
class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICS_TESTCASE_API UBasicMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBasicMovementComponent();

	void Move(const FVector2D& Input, float DeltaTime);
	void Look(const FVector2D& Input, float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LookSpeed = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinPitch = -89.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxPitch = 89.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	APawn* OwnerPawn = nullptr;

	UPROPERTY()
	UCameraComponent* Camera = nullptr;

		
};
