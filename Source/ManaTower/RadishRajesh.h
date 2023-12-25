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

	ARadishRajesh();//����Boss��

	virtual void BeginPlay() override;//�����ʼ�ĺ���

	virtual void Tick(float deltaSeconds) override;//ÿһ֡��Ҫִ�еĺ���

	UFUNCTION()

	void AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	//��ս��������
};
