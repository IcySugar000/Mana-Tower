// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "RoomBase.h"
#include "BossRoom.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API ABossRoom : public ARoomBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyBase> BossClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AEnemyBase* Boss;

	UFUNCTION(BlueprintNativeEvent)
	void OnBossDie(AEnemyBase* Enemy);

	void OnBossDie_Implementation(AEnemyBase* Enemy);
};
