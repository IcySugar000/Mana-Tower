// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "RadishRajesh.generated.h"

/**
 * 
 */
UCLASS()

class MANATOWER_API ARadishRajesh : public AEnemyBase
{
	GENERATED_BODY()

public:

	ARadishRajesh();//构造Boss怪

	virtual void BeginPlay() override;//构造后开始的函数

	virtual void Tick(float deltaSeconds) override;//每一帧所要执行的函数

	UFUNCTION()

	void AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	//近战攻击函数
};
