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
	float Health;//����״̬������ֵ
	bool IsDead;//�Ƿ�����
	float Speed;//�ٶ�
	float Attack;//������
	float Defense;//������
	bool IsHadReportedDead;//�Ƿ񱨸�������
	float AttackCD;//����CD
	float Distance;//����ҵľ���
	void UpdateFlipbook();

public:
	AEnemyBase();//�������

	virtual void BeginPlay() override;//�����ʼ�ĺ���
	virtual void Tick(float DeltaSeconds) override;//ÿ֡Ҫ���õĺ���

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;//��ȡ�˺�

	void Die();//����

	void MoveToPlayer();//�ƶ������

	UFUNCTION()
	void AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//������ʹ�����涨���һ�б�����Unreal����
	float MaxHealth;//�Ի����MaxHealth����ֵ����ֹ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//������ʹ�����涨���һ�б�����Unreal����
	float MaxAttackCD;//��󹥻�CD

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UPaperFlipbook*> FlipbookLibrary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageTypeClass = UEnemyBaseAttackDamageType::StaticClass();
};
