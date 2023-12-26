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
	AWoodenMan();//�������˹�

	virtual void BeginPlay() override;//�����ʼ�ĺ���
	virtual void Tick(float deltaSeconds) override;
	
	void AttackPlayer();
	void MoveToPlayer(float deltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//������ʹ�����涨���һ�б�����Unreal����
	float MaxMoveCD;//��󹥻�CD

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> BulletClass = ABulletBase::StaticClass();
};
