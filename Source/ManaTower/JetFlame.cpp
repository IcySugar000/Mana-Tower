// Fill out your copyright notice in the Description page of Project Settings.


#include "JetFlame.h"
#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AJetFlame::AJetFlame()					//火柱的生成
{
	LifeTime = MaxLifeTime;				//生存周期默认为最大的生存时间
	AttackCD = 0;                       // 放出去就可以打伤害
}

void AJetFlame::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	LifeTime -= DeltaSeconds;
	if (LifeTime <= 0) Destroy();

	if (AttackCD > 0) AttackCD = AttackCD > DeltaSeconds ? AttackCD - DeltaSeconds : 0.0;  // 攻击冷却计算，最小为0
	if (AttackCD <= 0) Attack();  // 冷却到了就攻击
}

void AJetFlame::SetSourcePlayer(APaperCharacter* player) {
	SourcePlayer = player;
}

void AJetFlame::Attack() {
	// TODO
	// 检测所有Overlap
	// 遍历Overlap，类型转换，给伤害

	AttackCD = MaxAttackCD;  // 重新设定cd
}




