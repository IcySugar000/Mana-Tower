// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "EnemyBaseAttackDamageType.h"
#include "EnemyBase.generated.h"

/**
 *
 */
UCLASS()
class MANATOWER_API AEnemyBase : public APaperCharacter
{
	GENERATED_BODY()

protected:
	float Health;//健康状态：生命值
	bool IsDead;//是否死亡
	float Speed;//速度
	float Attack;//攻击力
	float Defense;//防御力
	bool IsHadReportedDead;//是否报告死亡过
	float AttackCD;//攻击CD
	float Distance;//与玩家的距离
	void UpdateFlipbook();

public:
	AEnemyBase();//构造怪物

	virtual void BeginPlay() override;//构造后开始的函数
	virtual void Tick(float DeltaSeconds) override;//每帧要调用的函数

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;//获取伤害

	void Die();//死亡

	void MoveToPlayer();//移动向玩家

	UFUNCTION()
	void AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//这行是使得下面定义的一行变量被Unreal看到
	float MaxHealth;//对基类的MaxHealth赋初值，防止错误

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//这行是使得下面定义的一行变量被Unreal看到
	float MaxAttackCD;//最大攻击CD

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UPaperFlipbook*> FlipbookLibrary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageTypeClass = UEnemyBaseAttackDamageType::StaticClass();
};
