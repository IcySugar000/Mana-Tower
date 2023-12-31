// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperGroupedSpriteActor.h"
#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "RoomBase.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API ARoomBase : public APaperGroupedSpriteActor
{
	GENERATED_BODY()

private:
	UPaperGroupedSpriteComponent* GroupedSpriteComponent;
	FVector CenterLocation;

public:
	ARoomBase();
	void SetCenterLocation(FVector location);
	FVector GetCenterLocation();

	virtual void BeginPlay() override;

	void SetEdge(TArray<int> doors);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Edge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* EdgeOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> DetectSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EdgeLength = 1024;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EdgeWidth = 32;

	FScriptDelegate DelegateEnter;  // 进入房间的委托事件
};
