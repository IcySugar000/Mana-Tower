// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "EnemyBase.generated.h"

/**
 *
 */
UCLASS()
class MANATOWER_API AEnemyBase : public APaperCharacter
{
	GENERATED_BODY()

private:
	float Health;//健康状态：生命值
	bool IsDead;//是否死亡
	float speed;//速度
	float attack;//攻击力
	float defence;//防御力

	void UpdateFlipbook();

public:
	AEnemyBase();//构造怪物

	virtual void BeginPlay() override;//构造后开始的函数
	virtual void Tick(float DeltaSeconds) override;//每帧要调用的函数

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;//获取伤害

	void Die();//死亡

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//这行是使得下面定义的一行变量被Unreal看到
	float MaxHealth = 100;//对基类的MaxHealth赋初值，防止错误

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UPaperFlipbook*> FlipbookLibrary;

};
