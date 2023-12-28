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
	__int32 BossState = 0;//1:近战状态（兔子） 2：远攻状态（木头人） 3：冲刺状态（犀牛） 0:闲置状态
	TArray<float> StateSpeed = { 0,0.001,0,1200 };
	FVector Direction = FVector(0, 0, 0);
	float RecordTime;
	float IsHaveShort = 0;
public:

	ARadishRajesh();//构造Boss

	virtual void BeginPlay() override;//构造后开始的函数
	virtual void Tick(float deltaSeconds) override;//每一帧所要执行的函数

	UFUNCTION()
	void WhichState();

	UFUNCTION()
	void MoveToPlayer();

	UFUNCTION()
	void AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> BulletClass = ABulletBase::StaticClass();
};
