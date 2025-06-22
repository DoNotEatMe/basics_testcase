// MonsterStatsRow.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterStatsRow.generated.h"

USTRUCT(BlueprintType)
struct FMonsterStatsRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ExpReward = 0;
};
