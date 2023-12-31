// Fill out your copyright notice in the Description page of Project Settings.


#include "JetFlame.h"
#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AJetFlame::AJetFlame()					//火柱的生成
{
	LifeTime = MaxLifeTime;				//生存周期默认为最大的生存时间
	AttackCD = 0;                       // 放出去就可以打伤害
}

void AJetFlame::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);

	LifeTime -= DeltaSeconds;
	if (LifeTime <= 0) 
		Destroy();

	if (AttackCD > 0) 
		AttackCD = AttackCD > DeltaSeconds ? AttackCD - DeltaSeconds : 0.0;  // 攻击冷却计算，最小为0
	if (AttackCD <= 0) 
		Attack();  // 冷却到了就攻击
}

void AJetFlame::SetSourcePlayer(APaperCharacter* player) 
{
	SourcePlayer = player;
}

void AJetFlame::Attack() 
{

	// TODO
	// 检测所有Overlap
	// 遍历Overlap，类型转换，给伤害
	auto box = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));	//创建胶囊（即每一个物体周围都会有的范围标志物品）

	TArray<AActor*> OverlapActors;			//数组：用来存放和该伤害有交集的物品
	box->GetOverlappingActors(OverlapActors, AEnemyBase::StaticClass());	//这个有交集的物品集合是EnemyBase（即敌人）
	auto player = Cast<APlayerBase>(SourcePlayer);  // 造成伤害的玩家

	//如果这个交集存放的数组（敌人）不为空，即打到了敌人
	if (!OverlapActors.IsEmpty()) 
	{
		//由于火柱是造成所在路径上的所有敌人伤害的，所以我们需要遍历这个交集集合的所有元素（所有敌人）
		auto realDamage = UGameplayStatics::ApplyDamage(OverlapActors[0], Damage, GetController(), SourcePlayer, DamageTypeClass);
		if (player && player->IsVampirism) player->RestoreHealth(realDamage * 0.1);  // 吸血
	}
	AttackCD = MaxAttackCD;  // 重新设定cd
}




