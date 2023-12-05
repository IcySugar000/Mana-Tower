// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicCircleButton.h"

#include "MagicCircleLine.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"
#include "Components/VerticalBoxSlot.h"

void UMagicCircleButton::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMagicCircleButton::adjustLine()
{
	if (nowLining) {
		auto controller = GetWorld()->GetFirstPlayerController();
		float mouseLocationX = 0.0f;
		float mouseLocationY = 0.0f;
		if (controller) controller->GetMousePosition(mouseLocationX, mouseLocationY);
		float viewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
		FVector2D viewportPos = FVector2D(mouseLocationX, mouseLocationY) / viewportScale;

		UCanvasPanelSlot* lineSlot = Cast<UCanvasPanelSlot>(nowLining->Slot);
		FVector2D lineSize = lineSlot->GetSize();
		FVector2D deltaVector = viewportPos - lineSlot->GetPosition();

		lineSize.X = deltaVector.Size();
		lineSlot->SetSize(lineSize);

		float theta = FMath::Atan2(deltaVector.Y, deltaVector.X);
		theta = FMath::RadiansToDegrees(theta);
		// UE_LOG(LogTemp, Warning, TEXT("%lf"), theta);
		nowLining->SetRenderTransformAngle(theta);
	}
}

FReply UMagicCircleButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// UE_LOG(LogTemp, Warning, TEXT("Mouse Down at %d"), ButtonId);
	ButtonDown.ExecuteIfBound(ButtonId);
	return FReply::Handled();
}

void UMagicCircleButton::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	ButtonEnter.ExecuteIfBound(ButtonId);
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UMagicCircleButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	adjustLine();
}

void UMagicCircleButton::getLine()
{
	auto newLine = CreateWidget<UMagicCircleLine>(this, MagicCircleLineClass);
	if (MagicCircleLineClass) {

		nowLining = newLine;
		Lines.Emplace(newLine);

		newLine->AddToViewport();
		auto linePanelSlot = this->GetParent()->AddChild(newLine);
		UCanvasPanelSlot* lineSlot = Cast<UCanvasPanelSlot>(linePanelSlot);

		UCanvasPanelSlot* thisSlot = Cast<UCanvasPanelSlot>(this->Slot);
		FVector2D Position = thisSlot->GetPosition() + thisSlot->GetSize() / 2.0f;
		Position.Y -= lineSlot->GetSize().Y / 2.0f;
		lineSlot->SetPosition(Position);
		lineSlot->SetZOrder(-1);
		newLine->SetRenderTransformPivot(FVector2D(0.0f, 0.5f));

		adjustLine();
	}
}

void UMagicCircleButton::lockLine(FVector2D dstPos) {
	// UE_LOG(LogTemp, Warning, TEXT("Button Lockline"));

	UCanvasPanelSlot* thisSlot = Cast<UCanvasPanelSlot>(this->Slot);
	FVector2D Position = thisSlot->GetPosition() + thisSlot->GetSize() / 2.0f;

	UCanvasPanelSlot* lineSlot = Cast<UCanvasPanelSlot>(nowLining->Slot);
	FVector2D lineSize = lineSlot->GetSize();
	FVector2D deltaVector = dstPos - Position;

	lineSize.X = deltaVector.Size();
	lineSlot->SetSize(lineSize);

	float theta = FMath::Atan2(deltaVector.Y, deltaVector.X);
	// UE_LOG(LogTemp, Warning, TEXT("%lf %lf"), theta, FMath::Asin(lineSize.Y / 2.0f / deltaVector.Size()));
	theta = FMath::RadiansToDegrees(theta);
	nowLining->SetRenderTransformAngle(theta);

	nowLining = nullptr;
}

void UMagicCircleButton::clearLines()
{
	if (nowLining) {
		nowLining->RemoveFromParent();
		nowLining = nullptr;
	}
	for (auto line : Lines) line->RemoveFromParent();
	Lines.Empty();
}

void UMagicCircleButton::setCircle(UWidget* Circle)
{
	myCircle = Circle;
}
