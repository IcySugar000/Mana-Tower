// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndRoom.h"
#include "EnemyRoom.h"
#include "MazeGeneratorComponent.h"
#include "RoomBase.h"
#include "StatueRoom.h"
#include "StoreRoom.h"
#include "GameFramework/Actor.h"
#include "LevelMap.generated.h"

UCLASS()
class MANATOWER_API ALevelMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsInBound(int x, int y);
	ARoomBase* GetRoomInArray(int x, int y);

	const TArray< TPair<int32, int32> > Surrounds = { {1, 0}, {1, -1}, {0, -1}, {-1, 0}, {-1, 1}, {0, 1} };  // 按照0-5排序

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Size = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemySpawnNum = 3;  // 生成怪物个数

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NextLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMazeGeneratorComponent> MazeGenerator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARoomBase> RoomBase = ARoomBase::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARoomBase> EndRoom = AEndRoom::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARoomBase> EnemyRoom = AEnemyRoom::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARoomBase> StoreRoom = AStoreRoom::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARoomBase> StatueRoom = AStatueRoom::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAllowStore = true;  // 是否生成商店

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAllowStatue = true;  // 是否生成神像

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray< TSubclassOf<AEnemyBase> > EnemyTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ARoomBase*> RoomArray;  // 压缩储存的二维数组，大小为Size*Size
};
