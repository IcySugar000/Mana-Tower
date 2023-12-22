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
	UUserWidget* MyMainUI;

	virtual void BeginPlay() override;			//��ʼ��Ϸ
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void MoveRight(float ScaleValue);			//�����ƶ�
	void MoveUp(float ScaleValue);				//�����ƶ�
	void UpdateFlipbook();						//���Ķ���
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;//��һ�ȡ�˺���ȡ�˺�
	void Die();									//����

	float Attack;				//������
	float Defense;				//������
	float MaxHealth = 100;		//�������ֵ
	float Health;				//��ǰ����ֵ
	// float Defaultblood;		//�ܵ����˺�

	bool IsDead;                //�ж�����
	bool IsHadReportedDead;		//�Ƿ񱨸�������
	float MaxMana = 100;		//���ħ��ֵ
	float Mana;					//��ǰħ��ֵ

	int32 Coin = 0;               //�����еĽ����
	
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void CastSpell(TArray<uint8> ExistLines);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UPaperFlipbook*> FlipbookLibrary;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* MyMagicCircle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)

	UUserWidget* MyHealthbar;					//Widget MyHealthbar�Ĺ���

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)

	UUserWidget* MyManabar;					//Widget MyManabar�Ĺ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MagicCircleClass;				//MagicCircleClass������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")

	TSubclassOf<UUserWidget> MainUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarClass;				//HealthBarClass������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")

	TSubclassOf<UUserWidget> ManaBarClass;					//ManaBarClass������

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpellTranslator> Translator;

	UFUNCTION(BlueprintCallable)
	float GetHealth();				//��õ�ǰ����ֵ�ĺ���

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();			//����������ֵ�ĺ���

	UFUNCTION(BlueprintCallable)
	float GetMaxMana();				//������ħ��ֵ�ĺ���

	UFUNCTION(BlueprintCallable)
	float GetMana();				//��õ�ǰħ��ֵ�ĺ���

	UFUNCTION(BlueprintCallable)
	void LoseMana(float amount);    //ʧȥ����ֵ

	UFUNCTION(BlueprintCallable)
	void RestoreMana(float amount); //�ָ�����ֵ

	UFUNCTION(BlueprintCallable)
	int32 GetCoin();                //��ȡǮ������

	UFUNCTION(BlueprintCallable)
	void AddCoin(int32 num);        //����Ǯ������ 

	UFUNCTION(BlueprintCallable)
	bool RemoveCoin(int32 num);     //����Ǯ������

	APlayerBase();

};