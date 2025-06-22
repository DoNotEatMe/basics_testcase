// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BasicGameplayWidget.h"
#include "Character/CharacterStatsComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UBasicGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBasicGameplayWidget::BindStats(UCharacterStatsComponent* StatsComp)
{
	
	if (!StatsComp) return;

	BoundStats = StatsComp;

	StatsComp->OnHPChanged.AddDynamic(this, &UBasicGameplayWidget::UpdateHP);
	StatsComp->OnMPChanged.AddDynamic(this, &UBasicGameplayWidget::UpdateMP);
	StatsComp->OnEXPChanged.AddDynamic(this, &UBasicGameplayWidget::UpdateEXP);
	StatsComp->OnLVLChanged.AddDynamic(this, &UBasicGameplayWidget::UpdateLevel);

	UpdateHP();
	UpdateMP();
	UpdateEXP();
	UpdateLevel();

	UE_LOG(LogTemp, Display, TEXT("Binding Stats Component"));
}

void UBasicGameplayWidget::UpdateHP()
{
	if (BoundStats && HP_Bar)
	{
		float Ratio = BoundStats->CurrentHP / BoundStats->MaxHP;
		HP_Bar->SetPercent(Ratio);
	}
}

void UBasicGameplayWidget::UpdateMP()
{
	if (BoundStats && MP_Bar)
	{
		float Ratio = BoundStats->CurrentMP / BoundStats->MaxMP;
		MP_Bar->SetPercent(Ratio);
	}
}

void UBasicGameplayWidget::UpdateEXP()
{
	if (BoundStats && EXP_Bar)
	{
		float Ratio = BoundStats->EXP / BoundStats->EXPToNextLevel;
		EXP_Bar->SetPercent(Ratio);
	}
}

void UBasicGameplayWidget::UpdateLevel()
{
	if (BoundStats && Level)
	{
		Level->SetText(FText::AsNumber(BoundStats->Level));
	}
}

