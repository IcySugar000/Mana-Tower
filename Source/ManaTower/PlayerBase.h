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

	virtual void BeginPlay() override;			//开始游戏
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void MoveRight(float ScaleValue);
	void MoveUp(float ScaleValue);
	void UpdateFlipbook();

	float Attack;				//攻击力
	float Defense;				//防御力
	float MaxHealth;			//最大生命值
	float Health;				//当前生命值
	// float Defaultblood;		//受到的伤害
	
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void CastSpell(TArray<uint8> ExistLines);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UPaperFlipbook*> FlipbookLibrary;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* MyMagicCircle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)

	UUserWidget* MyHealthbar;					//Widget MyHealthbar

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MagicCircleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpellTranslator> Translator;

	UFUNCTION(BlueprintCallable)
	float GetHealth();				//获得当前生命值的函数

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();			//获得最大生命值的函数

	APlayerBase();

};