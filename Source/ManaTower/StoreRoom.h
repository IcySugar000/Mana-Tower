// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomBase.h"
#include "StoreRoom.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FStoreItem {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* Flipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;
};


UCLASS()
class MANATOWER_API AStoreRoom : public ARoomBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemNum = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> AvailableItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FStoreItem> StrToItem;

	UFUNCTION(BlueprintCallable)
	void GenerateItemList();
};
