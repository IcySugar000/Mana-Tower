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
protected:

	float Attack;

	float  Maxhealth = 300;	//最大生命值
	float Health;			//当前生命值
public:

	ARadishRajesh();//构造Boss怪

	virtual void BeginPlay() override;//构造后开始的函数

	virtual void Tick(float deltaSeconds) override;//每一帧所要执行的函数

	UFUNCTION()

	void AttackPlayer1(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	//近战攻击函数

	UFUNCTION()

	void AttackPlayer2();		//子弹射击函数

	UFUNCTION(BlueprintCallable)

	float GetHealth();				//获得Boss当前生命值的函数

	UFUNCTION(BlueprintCallable)

	float GetMaxHealth();			//获得Boss最大生命值的函数

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> BulletClass = ABulletBase::StaticClass();
};
