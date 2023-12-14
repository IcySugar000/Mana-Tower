// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire_DamageType.h"
#include "PaperCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
	APaperCharacter* SourcePlayer;		//火柱的伤害来源（默认为玩家）

public:

	AJetFlame();						//构造函数

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	float MaxLifeTime = 2;				//最大的存在时间

};
