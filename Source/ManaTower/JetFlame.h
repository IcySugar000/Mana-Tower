// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire_DamageType.h"
#include "PaperCharacter.h"
#include "JetFlame.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AJetFlame : public APaperCharacter
{
	GENERATED_BODY()

private:

	float LifeTime;						//火柱生存时间
	float Damage = 50;					//火柱造成的伤害
	float AttackCD;
	APaperCharacter* SourcePlayer;		//火柱的伤害来源（默认为玩家）

public:

	AJetFlame();						//构造函数
	virtual void Tick(float DeltaSeconds) override;

	void SetSourcePlayer(APaperCharacter* player);  // 设置源玩家
	void Attack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLifeTime = 2;				//最大的存在时间

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAttackCD = 0.5;
};
