// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Rhino.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API ARhino : public AEnemyBase
{
	GENERATED_BODY()
	
private:
	float RushTime;
	FVector Direction = FVector(0, 0, 0);
public:
	ARhino();//����Ϭţ

	virtual void BeginPlay() override;//�����ʼ�ĺ���
	virtual void Tick(float deltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//������ʹ�����涨���һ�б�����Unreal����
	float MaxRushTime = 2;

	UFUNCTION()
	void AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
