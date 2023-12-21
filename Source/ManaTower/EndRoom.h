// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomBase.h"
#include "EndRoom.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AEndRoom : public ARoomBase
{
	GENERATED_BODY()

private:
	FString NextLevel;

public:
	UFUNCTION(BlueprintCallable)
	FString GetNextLevel();

	void SetNextLevel(FString nextLevel);
};
