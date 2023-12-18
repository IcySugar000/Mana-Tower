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
	void MoveRight(float ScaleValue);			//左右移动
	void MoveUp(float ScaleValue);				//上下移动
	void UpdateFlipbook();						//更改动画
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;//玩家获取伤害获取伤害
	void Die();									//死亡

	float Attack;				//攻击力
	float Defense;				//防御力
	float MaxHealth = 100;		//最大生命值
	float Health;				//当前生命值
	// float Defaultblood;		//受到的伤害

	bool IsDead;                //判断死亡
	bool IsHadReportedDead;		//是否报告死亡过
	float MaxMana = 100;		//最大魔法值
	float Mana;					//当前魔法值
	// float CostMana;				//消耗的魔法值
	
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void CastSpell(TArray<uint8> ExistLines);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UPaperFlipbook*> FlipbookLibrary;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* MyMagicCircle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)

	UUserWidget* MyHealthbar;					//Widget MyHealthbar的构建

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)

	UUserWidget* MyManabar;					//Widget MyManabar的构建

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MagicCircleClass;				//MagicCircleClass的声明

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarClass;				//HealthBarClass的声明

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")

	TSubclassOf<UUserWidget> ManaBarClass;					//ManaBarClass的声明

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpellTranslator> Translator;

	UFUNCTION(BlueprintCallable)
	float GetHealth();				//获得当前生命值的函数

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();			//获得最大生命值的函数

	UFUNCTION(BlueprintCallable)
	float GetMaxMana();				//获得最大魔法值的函数

	UFUNCTION(BlueprintCallable)
	float GetMana();				//获得当前魔法值的函数

	UFUNCTION(BlueprintCallable)
	void LoseMana(float amount);

	UFUNCTION(BlueprintCallable)
	void RestoreMana(float amount);

	APlayerBase();

};