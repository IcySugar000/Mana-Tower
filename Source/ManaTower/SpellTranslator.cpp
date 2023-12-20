// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTranslator.h"

#include "PlayerBase.h"

class APlayerBase;
// Sets default values for this component's properties
USpellTranslator::USpellTranslator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void USpellTranslator::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USpellTranslator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpellTranslator::CastSpell(FName Name, int Rotation) {
}

void USpellTranslator::SetButtonNum(int32 TotalButtonNum) {
	ButtonNum = TotalButtonNum;
}

void USpellTranslator::Translate(TArray<uint8> InputActivator) {
	UE_LOG(LogTemp, Warning, TEXT("Translating..."));
	for (auto digit : InputActivator) UE_LOG(LogTemp, Warning, TEXT("%d"), digit);
	if (MagicList.IsEmpty()) UE_LOG(LogTemp, Warning, TEXT("Empty List!"));

	for (auto spell : MagicList) {
		TArray < TArray<uint8> > allActivators;  // 用于储存某activator变换后的所有activator
		allActivators.Emplace(spell.Activator);

		if (spell.CanStartAtAny) {
			TArray copySpell(spell.Activator);
			copySpell.RemoveAt(copySpell.Num() - 1);
			allActivators.RemoveAt(0);

			for (int i = 0; i < copySpell.Num(); ++i) {
				TArray<uint8> tempSpell;
				for (int j = 0; j < copySpell.Num(); ++j) tempSpell.Emplace(copySpell[(i + j) % copySpell.Num()]);
				tempSpell.Emplace(copySpell[i]);
				allActivators.Emplace(tempSpell);
			}
		}

		if (spell.CanReverse) {
			int32 num = allActivators.Num();
			for (int i = 0; i < num; ++i) {
				TArray<uint8> tempSpell;
				for (uint8 digit : allActivators[i]) tempSpell.EmplaceAt(0, digit);
				allActivators.Emplace(tempSpell);
			}
		}

		if (spell.CanTurn) {
			for (auto s : allActivators) {
				for (int i = 0; i < ButtonNum; ++i) {
					TArray<uint8> tempSpell;
					for (uint8 digit : spell.Activator) tempSpell.Emplace((digit + i) % ButtonNum);
					if (tempSpell == InputActivator) {
						// 检测魔力是否足够
						if(Cast<APlayerBase>(GetOwner())->GetMana() >= spell.RequiredMana) {
							Cast<APlayerBase>(GetOwner())->LoseMana(spell.RequiredMana);
							CastSpell(spell.Name, i);
							UE_LOG(LogTemp, Warning, TEXT("%s"), *spell.Name.ToString());
							return;
						}
					}
				}
			}
		}
		else {
			for (auto s : allActivators) {
				if (s == InputActivator) {
					// 检测魔力是否足够
					if (Cast<APlayerBase>(GetOwner())->GetMana() >= spell.RequiredMana) {
						Cast<APlayerBase>(GetOwner())->LoseMana(spell.RequiredMana);
						CastSpell(spell.Name);
						UE_LOG(LogTemp, Warning, TEXT("%s"), *spell.Name.ToString());
						return;
					}
				}
			}
		}
	}
}
