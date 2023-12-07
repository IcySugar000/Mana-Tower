// Fill out your copyright notice in the Description page of Project Settings.


#include "FlaminaSpellTranslator.h"

void UFlaminaSpellTranslator::CastSpell(FName Name, int Rotation) {
	Super::CastSpell(Name, Rotation);

	if (Name == "Fireball") {
		Fireball(Rotation);
	}
}

void UFlaminaSpellTranslator::Fireball(int Rotation) {
	UE_LOG(LogTemp, Warning, TEXT("Fireball at Rotation: %d"), Rotation);
}
