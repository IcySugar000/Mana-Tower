// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire_DamageType.h"
#include "PaperCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FireballProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AFireballProjectile : public APaperCharacter
{
	GENERATED_BODY()
	
private:
	float LifeTime;						//火球生存周期
	float Damage = 25;					//火球伤害
	APaperCharacter* SourcePlayer;		//伤害来源（默认为玩家）

	void DetectTarget();				//设置火球追踪效果

public:
	AFireballProjectile();				//构造函数
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetDamage(float newDamage);

	void SetSourcePlayer(APaperCharacter* player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> DetectSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageTypeClass = UFire_DamageType::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLifeTime = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectRange = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Acceleration = 10000.0;
};
