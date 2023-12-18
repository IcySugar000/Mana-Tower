// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "PinkBunny.generated.h"

/**
 *
 */
UCLASS()
class MANATOWER_API APinkBunny : public AEnemyBase
{
	GENERATED_BODY()

public:
	APinkBunny();//构造粉毛兔子怪

	virtual void BeginPlay() override;//构造后开始的函数

	UFUNCTION()
	void AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    
};