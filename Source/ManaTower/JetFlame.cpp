// Fill out your copyright notice in the Description page of Project Settings.


#include "JetFlame.h"
#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AJetFlame::AJetFlame()					//����������
{
	LifeTime = MaxLifeTime;				//��������Ĭ��Ϊ��������ʱ��
	AttackCD = 0;                       // �ų�ȥ�Ϳ��Դ��˺�
}

void AJetFlame::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	LifeTime -= DeltaSeconds;
	if (LifeTime <= 0) Destroy();

	if (AttackCD > 0) 
		AttackCD = AttackCD > DeltaSeconds ? AttackCD - DeltaSeconds : 0.0;  // ������ȴ���㣬��СΪ0
	if (AttackCD <= 0) 
		Attack();  // ��ȴ���˾͹���
}

void AJetFlame::SetSourcePlayer(APaperCharacter* player) {
	SourcePlayer = player;
}

void AJetFlame::Attack() {

	// TODO
	// �������Overlap
	// ����Overlap������ת�������˺�
	auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));	//�������ң���ÿһ��������Χ�����еķ�Χ��־��Ʒ��

	TArray<AActor*> OverlapActors;			//���飺������ź͸��˺��н�������Ʒ
	capsule->GetOverlappingActors(OverlapActors, AEnemyBase::StaticClass());	//����н�������Ʒ������EnemyBase�������ˣ�

	//������������ŵ����飨���ˣ���Ϊ�գ������˵���
	if (!OverlapActors.IsEmpty()) {
		//���ڻ������������·���ϵ����е����˺��ģ�����������Ҫ��������������ϵ�����Ԫ�أ����е��ˣ�
		UGameplayStatics::ApplyDamage(OverlapActors[0], Damage, GetController(), SourcePlayer, DamageTypeClass);
		//for (unsigned int role = 0; role < OverlapActors.GetTypeSize(); role++) {
		//	UGameplayStatics::ApplyDamage(OverlapActors[role], Damage, GetController(), SourcePlayer, DamageTypeClass);
		//}
		
	}
	AttackCD = MaxAttackCD;  // �����趨cd
}




