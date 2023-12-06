// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellTranslator.generated.h"

USTRUCT(Blueprintable)
struct FMagicSpell {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<uint8> Activator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanReverse = false;  // 是否可以反向绘制

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanTurn = false;  // 是否可以转动方向绘制

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanStartAtAny = false;  // 是否可以从任何点开始绘制
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MANATOWER_API USpellTranslator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellTranslator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMagicSpell> MagicList;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int32 ButtonNum;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetButtonNum(int32 TotalButtonNum);
	void Translate(TArray<uint8> InputActivator);
};
