// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeGeneratorComponent.h"
#include "RoomBase.h"
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
	TObjectPtr<UMazeGeneratorComponent> MazeGenerator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARoomBase> RoomBase = ARoomBase::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ARoomBase*> RoomArray;  // 压缩储存的二维数组，大小为Size*Size
};
