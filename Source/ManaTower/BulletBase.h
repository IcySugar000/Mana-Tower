// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnemyBaseAttackDamageType.h"
#include "BulletBase.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API ABulletBase : public APaperCharacter
{
	GENERATED_BODY()

protected:
	float LifeTime;//�ӵ�ʣ�����ʱ��
	float Damage = 25;//�ӵ���ɵ��˺�
	APaperCharacter* Source;//�˺������Դ

public:
	ABulletBase();//���캯��
	virtual void BeginPlay() override;//�����ʼ�ĺ���
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetDamage(float newDamage);

	void SetSource(APaperCharacter* source);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageTypeClass = UEnemyBaseAttackDamageType::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLifeTime = 5;//����ӵ�����ʱ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1000;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsFromEnemy = true;//�Ƿ�������
};
