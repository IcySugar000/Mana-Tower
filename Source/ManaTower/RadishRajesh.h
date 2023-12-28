// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "BulletBase.h"
#include "RadishRajesh.generated.h"

/**
 *
 */
UCLASS()

class MANATOWER_API ARadishRajesh : public AEnemyBase
{
	GENERATED_BODY()

private:
	__int32 BossState = 0;//1:��ս״̬�����ӣ� 2��Զ��״̬��ľͷ�ˣ� 3�����״̬��Ϭţ�� 0:����״̬
	TArray<float> StateSpeed = { 0,0.001,0,1200 };
	FVector Direction = FVector(0, 0, 0);
	float RecordTime;
	float IsHaveShort = 0;
public:

	ARadishRajesh();//����Boss

	virtual void BeginPlay() override;//�����ʼ�ĺ���
	virtual void Tick(float deltaSeconds) override;//ÿһ֡��Ҫִ�еĺ���

	UFUNCTION()
	void WhichState();

	UFUNCTION()
	void MoveToPlayer();

	UFUNCTION()
	void AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> BulletClass = ABulletBase::StaticClass();
};
