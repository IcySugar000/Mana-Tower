// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MagicCircleButton.generated.h"

class UMagicCircleLine;
/**
 * 
 */

DECLARE_DELEGATE_OneParam(FButtonDownDelegate, uint8);
DECLARE_DELEGATE_OneParam(FButtonEnterDelegate, uint8);

UCLASS()
class MANATOWER_API UMagicCircleButton : public UUserWidget
{
	GENERATED_BODY()

private:
	void adjustLine();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	UMagicCircleLine* nowLining;

public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void getLine();

	void lockLine(FVector2D dstPos);

	void setCircle(UWidget* Circle);

	void clearLines();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidget* myCircle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ButtonId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UMagicCircleLine*> Lines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MagicCircleLineClass;

	FButtonDownDelegate ButtonDown;

	FButtonEnterDelegate ButtonEnter;
};
