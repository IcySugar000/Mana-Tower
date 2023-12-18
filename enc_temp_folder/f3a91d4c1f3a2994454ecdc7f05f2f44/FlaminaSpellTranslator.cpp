// Fill out your copyright notice in the Description page of Project Settings.


#include "FlaminaSpellTranslator.h"
#include "FireballProjectile.h"
#include "PlayerBase.h"

class APlayerBase;

void UFlaminaSpellTranslator::CastSpell(FName Name, int Rotation) {
	Super::CastSpell(Name, Rotation);

	UE_LOG(LogTemp, Warning, TEXT("CASTING: %s"), *Name.ToString());

	if (Name == "Fireball") {
		Fireball(Rotation);
	}
	else if(Name == "Restore Mana") {
		RestoreMana();
	}
}

void UFlaminaSpellTranslator::Fireball(int Rotation) {
	UE_LOG(LogTemp, Warning, TEXT("Fireball at Rotation: %d"), Rotation);

	auto myFireball = GetWorld()->SpawnActor<AFireballProjectile>(FireballClass,
		GetOwner()->GetActorLocation(),
		FRotator(-60.0 * Rotation, 0.0, 0.0));
	myFireball->SetSourcePlayer(GetTypedOuter<APaperCharacter>());
}

void UFlaminaSpellTranslator::RestoreMana() {
	UE_LOG(LogTemp, Warning, TEXT("Restoring Mana"));
	auto player = Cast<APlayerBase>(GetOwner());
	if (player) {
		player->RestoreMana(10);
		UE_LOG(LogTemp, Warning, TEXT("Restoring Mana2"));
	}
}
