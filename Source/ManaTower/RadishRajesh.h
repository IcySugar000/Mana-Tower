// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "BulletBase.h"
#include "RadishRajesh.generated.h"

/**
 * 
 */
UCLASS()

class MANATOWER_API ARadishRajesh : public AEnemyBase
{
	GENERATED_BODY()
protected:

	float Attack;

	float  Maxhealth = 300;	//�������ֵ
	float Health;			//��ǰ����ֵ
public:

	ARadishRajesh();//����Boss��

	virtual void BeginPlay() override;//�����ʼ�ĺ���

	virtual void Tick(float deltaSeconds) override;//ÿһ֡��Ҫִ�еĺ���

	UFUNCTION()

	void AttackPlayer1(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	//��ս��������

	UFUNCTION()

	void AttackPlayer2();		//�ӵ��������

	UFUNCTION(BlueprintCallable)

	float GetHealth();				//���Boss��ǰ����ֵ�ĺ���

	UFUNCTION(BlueprintCallable)

	float GetMaxHealth();			//���Boss�������ֵ�ĺ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> BulletClass = ABulletBase::StaticClass();
};
