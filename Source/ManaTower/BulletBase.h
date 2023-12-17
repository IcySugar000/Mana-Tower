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
	float LifeTime;//子弹剩余存在时间
	float Damage = 25;//子弹造成的伤害
	APaperCharacter* Source;//伤害造成来源

public:
	ABulletBase();//构造函数
	virtual void BeginPlay() override;//构造后开始的函数
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
	float MaxLifeTime = 5;//最大子弹存在时间

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1000;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsFromEnemy = true;//是否来自于
};
