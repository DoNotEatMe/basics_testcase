// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICS_TESTCASE_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxMP = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float EXP = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float EXPToNextLevel = 100.f;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatChanged OnHPChanged;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatChanged OnMPChanged;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatChanged OnEXPChanged;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatChanged OnLVLChanged;

	
	
	FTimerHandle MPRegenTimer;
	
	UPROPERTY(EditAnywhere, Category="Stats|MP")
	float MPRegenRate = 2.0f; 

	UPROPERTY(EditAnywhere, Category="Stats|MP")
	float MPRegenInterval = 1.0f;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void CheckLevelUp();

public:
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

	UFUNCTION(BlueprintCallable)
	void UseMP(float Amount);

	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable)
	void RestoreMP(float Amount);

	UFUNCTION(BlueprintCallable)
	void GainEXP(float Amount);

	UFUNCTION()
	void InitializeStats();

	UFUNCTION()
	void RegenMPTick();

	void StartMPRegen();
	void StopMPRegen();

	
		
};


