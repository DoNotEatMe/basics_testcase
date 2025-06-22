// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/BasicHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/BasicGameplayWidget.h"


void ABasicHUD::SpawnUI(UCharacterStatsComponent* Stats)
{
	if (APlayerController* Controller = GetOwningPlayerController())
	{
		if (GameplayWidgetClass && !GameplayWidget)
		{
			GameplayWidget = CreateWidget<UBasicGameplayWidget>(Controller, GameplayWidgetClass);
			GameplayWidget->BindStats(Stats);
			GameplayWidget->AddToViewport();
		}
	}
}

