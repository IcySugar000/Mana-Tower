// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "BulletBase.h"
#include "WoodenMan.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AWoodenMan : public AEnemyBase
{
	GENERATED_BODY()
	
private:
	float MoveCD;

public:
	AWoodenMan();//构造树人怪

	virtual void BeginPlay() override;//构造后开始的函数
	virtual void Tick(float deltaSeconds) override;
	
	void AttackPlayer();
	void MoveToPlayer(float deltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//这行是使得下面定义的一行变量被Unreal看到
	float MaxMoveCD;//最大攻击CD

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> BulletClass = ABulletBase::StaticClass();
};
