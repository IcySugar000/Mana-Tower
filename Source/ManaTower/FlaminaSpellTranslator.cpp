// Fill out your copyright notice in the Description page of Project Settings.


#include "FlaminaSpellTranslator.h"

#include "FireballProjectile.h"

void UFlaminaSpellTranslator::CastSpell(FName Name, int Rotation) {
	Super::CastSpell(Name, Rotation);

	if (Name == "Fireball") {
		Fireball(Rotation);
	}
}

void UFlaminaSpellTranslator::Fireball(int Rotation) {
	UE_LOG(LogTemp, Warning, TEXT("Fireball at Rotation: %d"), Rotation);

	auto myFireball = GetWorld()->SpawnActor<AFireballProjectile>(FireballClass,
		GetOwner()->GetActorLocation(),
		FRotator(-60.0 * Rotation, 0.0, 0.0));
}
