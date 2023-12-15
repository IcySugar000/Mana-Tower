// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireballProjectile.h"
#include "Bullet.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API ABullet : public AFireballProjectile
{
	GENERATED_BODY()

protected:
	float Damage = 12;	//子弹伤害

public:
	ABullet();

	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);//击中效果
	
	void DetectTarget();//重定义使得无法自动追踪
};
