// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterStatsComponent.h"

// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCharacterStatsComponent::TakeDamage(float Amount)
{
	CurrentHP = FMath::Clamp(CurrentHP - Amount, 0.f, MaxHP);
	OnHPChanged.Broadcast();
}

void UCharacterStatsComponent::Heal(float Amount)
{
	CurrentHP = FMath::Clamp(CurrentHP + Amount, 0.f, MaxHP);
	OnHPChanged.Broadcast();
}

void UCharacterStatsComponent::UseMP(float Amount)
{
	CurrentMP = FMath::Clamp(CurrentMP - Amount, 0.f, MaxMP);
	OnMPChanged.Broadcast();
}

void UCharacterStatsComponent::RestoreMP(float Amount)
{
	CurrentMP = FMath::Clamp(CurrentMP + Amount, 0.f, MaxMP);
	OnMPChanged.Broadcast();
}

void UCharacterStatsComponent::GainEXP(float Amount)
{
	EXP += Amount;
	OnEXPChanged.Broadcast();
	CheckLevelUp();
}

void UCharacterStatsComponent::CheckLevelUp()
{
	while (EXP >= EXPToNextLevel)
	{
		EXP -= EXPToNextLevel;
		Level++;
		MaxHP += 10.f;
		MaxMP += 5.f;

		CurrentHP = MaxHP;
		CurrentMP = MaxMP;
		EXPToNextLevel *= 1.25f;

		OnHPChanged.Broadcast();
		OnMPChanged.Broadcast();
		OnEXPChanged.Broadcast();
		OnLVLChanged.Broadcast();
	}
}

void UCharacterStatsComponent::InitializeStats()
{
	CurrentHP = MaxHP;
	CurrentMP = MaxMP;
}