// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnCharacterBase.generated.h"

class UCharacterStatsComponent;
class UCameraComponent;
class UCapsuleComponent;
class UInputAction;
class UInputMappingContext;
class UBasicMovementComponent;
struct FInputActionValue;

UCLASS()
class BASICS_TESTCASE_API APawnCharacterBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnCharacterBase();

	UPROPERTY(VisibleAnywhere)
	UBasicMovementComponent* MovementComponent;
	
	UPROPERTY(VisibleAnywhere)
	UCharacterStatsComponent* StatsComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputFire;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputHeal;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputAddMP;
	
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UFUNCTION()
	void HandleMove(const FInputActionValue& Value);

	UFUNCTION()
	void HandleLook(const FInputActionValue& Value);

	UFUNCTION()
	void HandleFire(const FInputActionValue& Value);

	UFUNCTION()
	void HandleHeal(const FInputActionValue& Value);

	UFUNCTION()
	void HandleAddMP(const FInputActionValue& Value);

	
	

};




