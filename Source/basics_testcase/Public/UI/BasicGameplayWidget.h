// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasicGameplayWidget.generated.h"

class UTextBlock;
class UProgressBar;
class UCharacterStatsComponent;
/**
 * 
 */
UCLASS()
class BASICS_TESTCASE_API UBasicGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HP_Bar = nullptr;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* MP_Bar = nullptr;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* EXP_Bar = nullptr;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Level = nullptr;

	UFUNCTION(BlueprintCallable)
	void BindStats(UCharacterStatsComponent* StatsComp);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	UCharacterStatsComponent* BoundStats = nullptr;

	UFUNCTION()
	void UpdateHP();

	UFUNCTION()
	void UpdateMP();

	UFUNCTION()
	void UpdateEXP();

	UFUNCTION()
	void UpdateLevel();
};
