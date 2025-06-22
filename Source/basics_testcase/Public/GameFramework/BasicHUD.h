// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BasicHUD.generated.h"

class UCharacterStatsComponent;
class UBasicGameplayWidget;
/**
 * 
 */
UCLASS()
class BASICS_TESTCASE_API ABasicHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameplayWidgetClass;

	UFUNCTION()
	void SpawnUI(UCharacterStatsComponent* Stats);

protected:

	UPROPERTY()
	UBasicGameplayWidget* GameplayWidget = nullptr;
};
