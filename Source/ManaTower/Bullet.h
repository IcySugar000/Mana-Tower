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
	float Damage = 12;	//�ӵ��˺�

public:
	ABullet();

	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);//����Ч��
	
	void DetectTarget();//�ض���ʹ���޷��Զ�׷��
};
