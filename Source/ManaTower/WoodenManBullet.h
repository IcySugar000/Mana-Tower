// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"
#include "WoodenManBullet.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AWoodenManBullet : public ABulletBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;//构造后开始的函数
};
