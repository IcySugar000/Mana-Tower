// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "SpellTranslator.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBase.generated.h"

/**
 *
 */

UCLASS()
class MANATOWER_API APlayerBase : public APaperCharacter
{
	GENERATED_BODY()

protected:
	APlayerController* Controller;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void MoveRight(float ScaleValue);
	void MoveUp(float ScaleValue);
	void UpdateFlipbook();

	float Attckrate;
	float Defencerate;
	float Maxblood;
	float Currentblood;
	float Defaultblood;

	float Is_dead(float Currentblood)
	{
		if (Currentblood == 0)
			return 0;
		else
			return Currentblood;
	}

	
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void CastSpell(TArray<uint8> ExistLines);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UPaperFlipbook*> FlipbookLibrary;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* MyMagicCircle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MagicCircleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpellTranslator> Translator;

	APlayerBase();

};