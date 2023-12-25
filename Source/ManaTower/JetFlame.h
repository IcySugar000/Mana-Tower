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

	float LifeTime;						//��������ʱ��
	float Damage = 50;					//������ɵ��˺�
	float AttackCD;						//������CDֵ
	APaperCharacter* SourcePlayer;		//�������˺���Դ��Ĭ��Ϊ��ң�

public:

	AJetFlame();						//���캯��
	virtual void Tick(float DeltaSeconds) override;

	void SetSourcePlayer(APaperCharacter* player);  // ����Դ���

	void Attack();						//�������˺��ĺ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLifeTime = 2;				//���Ĵ���ʱ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAttackCD = 0.5;			//�����������CD

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	TSubclassOf<UDamageType> DamageTypeClass = UFire_DamageType::StaticClass();	//�������˺�����
};
