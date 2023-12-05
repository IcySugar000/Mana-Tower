// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicCircleButton.h"
#include "PaperCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "MagicCircle.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FCastSpellDelegate, TArray<uint8>);

UCLASS()
class MANATOWER_API UMagicCircle : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TArray< TArray<bool> > LineRecord;  // ���ڱ��ĳ�����Ƿ����
	TArray<uint8> ExistLines;  // ���ڼ�¼���ߵ�˳��

	uint8 StartBtnId;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void ClearDrawing();

	UFUNCTION()
	void onButtonDown(uint8 buttonId);

	UFUNCTION()
	void onButtonEnter(uint8 buttonId);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<uint8, UMagicCircleButton*> ButtonMap;

	UPROPERTY(VisibleAnywhere)
	bool isDrawing = false;

	FCastSpellDelegate CastSpell;
};
