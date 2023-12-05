// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicCircle.h"
#include "InputCoreTypes.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"

void UMagicCircle::NativeConstruct()
{
	Super::NativeConstruct();

	this->WidgetTree->ForEachWidget([&](UWidget* widget) {  // ������widget������UI���
		if(widget->GetClass()->IsChildOf(UMagicCircleButton::StaticClass())) {  // �ж��Ƿ�Ϊbutton
			auto myButton = Cast<UMagicCircleButton, UWidget>(widget);  // ֱ��ת��Ϊbutton
			myButton->ButtonDown.BindUFunction(this, "onButtonDown");  // �󶨰���ί��
			myButton->ButtonEnter.BindUFunction(this, "onButtonEnter");  // �󶨽��밴ťί��
			ButtonMap.Emplace(myButton->ButtonId, myButton);  // ��¼��Map
		}
		});

	auto const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CastSpell.BindUFunction(player, "CastSpell");

	TArray<bool> tmpArray;
	tmpArray.Init(false, ButtonMap.Num());
	for (int i = 0; i < ButtonMap.Num(); ++i) {
		LineRecord.Emplace(tmpArray);
	}
}

void UMagicCircle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(isDrawing) {
		if(Controller->WasInputKeyJustReleased(EKeys::LeftMouseButton)) {
			CastSpell.ExecuteIfBound(ExistLines);
			ClearDrawing();
		}
	}
}

void UMagicCircle::ClearDrawing()
{
	// UE_LOG(LogTemp, Warning, TEXT("Circle: clear drawing"));
	for(auto &elem: ButtonMap) {
		auto btn = elem.Value;
		btn->clearLines();
	}
	for (int i = 0; i < ButtonMap.Num(); ++i) {
		for (int j = 0; j < ButtonMap.Num(); ++j) {
			LineRecord[i][j] = false;
		}
	}
	ExistLines.Empty();

	StartBtnId = 0;
	isDrawing = false;
}

void UMagicCircle::onButtonDown(uint8 buttonId)
{
	// UE_LOG(LogTemp, Warning, TEXT("Circle: onButtonDown"));
	if(!isDrawing) {  // ��ʼ�滭
		isDrawing = true;
		StartBtnId = buttonId;
		ExistLines.Emplace(StartBtnId);
		ButtonMap[buttonId]->getLine();
	}
}

void UMagicCircle::onButtonEnter(uint8 buttonId) {
	// UE_LOG(LogTemp, Warning, TEXT("Circle: onButtonEnter"));
	if (isDrawing && buttonId != StartBtnId && !LineRecord[StartBtnId][buttonId]) {
		auto endSlot = Cast<UCanvasPanelSlot>(ButtonMap[buttonId]->Slot);
		FVector2D dstPos = endSlot->GetPosition() + endSlot->GetSize() / 2.0f;
		ButtonMap[StartBtnId]->lockLine(dstPos);

		LineRecord[StartBtnId][buttonId] = true;
		ExistLines.Emplace(buttonId);

		StartBtnId = buttonId;

		ButtonMap[buttonId]->getLine();
	}
}
