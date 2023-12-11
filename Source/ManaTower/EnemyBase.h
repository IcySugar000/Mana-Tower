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
	float Health;//����״̬������ֵ
	bool IsDead;//�Ƿ�����
	float speed;//�ٶ�
	float attack;//������
	float defence;//������

	void UpdateFlipbook();

public:
	AEnemyBase();//�������

	virtual void BeginPlay() override;//�����ʼ�ĺ���
	virtual void Tick(float DeltaSeconds) override;//ÿ֡Ҫ���õĺ���

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;//��ȡ�˺�

	void Die();//����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//������ʹ�����涨���һ�б�����Unreal����
	float MaxHealth = 100;//�Ի����MaxHealth����ֵ����ֹ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UPaperFlipbook*> FlipbookLibrary;

};
