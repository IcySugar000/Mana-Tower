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
	ARhino();//构造犀牛

	virtual void BeginPlay() override;//构造后开始的函数
	virtual void Tick(float deltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//这行是使得下面定义的一行变量被Unreal看到
	float MaxRushTime = 2;

	UFUNCTION()
	void AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
