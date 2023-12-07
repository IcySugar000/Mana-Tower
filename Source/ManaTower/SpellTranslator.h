// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
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
	bool CanReverse = false;  // �Ƿ���Է������

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanTurn = false;  // �Ƿ����ת���������

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanStartAtAny = false;  // �Ƿ���Դ��κε㿪ʼ����
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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
	UPROPERTY()
	APaperCharacter* MyCharacter;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void CastSpell(FName Name, int Rotation = 0);

	void SetButtonNum(int32 TotalButtonNum);
	void Translate(TArray<uint8> InputActivator);
};