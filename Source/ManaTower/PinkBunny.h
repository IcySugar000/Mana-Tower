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
	APinkBunny();//�����ë���ӹ�

	virtual void BeginPlay() override;//�����ʼ�ĺ���

};