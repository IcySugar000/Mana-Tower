// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "WoodenMan.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AWoodenMan : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AWoodenMan();//�������˹�

	virtual void BeginPlay() override;//�����ʼ�ĺ���
	
	
	void AttackPlayer();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> BulletClass = ABullet::StaticClass();
};
