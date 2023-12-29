// Fill out your copyright notice in the Description page of Project Settings.


#include "JetFlame.h"
#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AJetFlame::AJetFlame()					//����������
{
	LifeTime = MaxLifeTime;				//��������Ĭ��Ϊ��������ʱ��
	AttackCD = 0;                       // �ų�ȥ�Ϳ��Դ��˺�
}

void AJetFlame::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);

	LifeTime -= DeltaSeconds;
	if (LifeTime <= 0) 
		Destroy();

	if (AttackCD > 0) 
		AttackCD = AttackCD > DeltaSeconds ? AttackCD - DeltaSeconds : 0.0;  // ������ȴ���㣬��СΪ0
	if (AttackCD <= 0) 
		Attack();  // ��ȴ���˾͹���
}

void AJetFlame::SetSourcePlayer(APaperCharacter* player) 
{
	SourcePlayer = player;
}

void AJetFlame::Attack() 
{

	// TODO
	// �������Overlap
	// ����Overlap������ת�������˺�
	auto box = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));	//�������ң���ÿһ��������Χ�����еķ�Χ��־��Ʒ��

	TArray<AActor*> OverlapActors;			//���飺������ź͸��˺��н�������Ʒ
	box->GetOverlappingActors(OverlapActors, AEnemyBase::StaticClass());	//����н�������Ʒ������EnemyBase�������ˣ�
	auto player = Cast<APlayerBase>(SourcePlayer);  // ����˺������

	//������������ŵ����飨���ˣ���Ϊ�գ������˵���
	if (!OverlapActors.IsEmpty()) 
	{
		//���ڻ������������·���ϵ����е����˺��ģ�����������Ҫ��������������ϵ�����Ԫ�أ����е��ˣ�
		auto realDamage = UGameplayStatics::ApplyDamage(OverlapActors[0], Damage, GetController(), SourcePlayer, DamageTypeClass);
		if (player && player->IsVampirism) player->RestoreHealth(realDamage * 0.1);  // ��Ѫ
	}
	AttackCD = MaxAttackCD;  // �����趨cd
}




