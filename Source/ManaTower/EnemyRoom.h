// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "RoomBase.h"
#include "EnemyRoom.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AEnemyRoom : public ARoomBase
{
	GENERATED_BODY()

private:
	bool IsHadEntered = false;
	
public:
	virtual void BeginPlay() override;

	void SetEnemyTypes(TArray< TSubclassOf<AEnemyBase> > types);
	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void OnEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpawnNum = 3;  // 生成怪物个数，之后可以改成多波

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray< TSubclassOf<AEnemyBase> > EnemyTypes;  // 生成怪物种类

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AEnemyBase*> EnemyInRoom;
};
