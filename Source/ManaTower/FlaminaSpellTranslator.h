// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireballProjectile.h"
#include "JetFlame.h"
#include "SpellTranslator.h"
#include "FlaminaSpellTranslator.generated.h"

/**
 *
 */
UCLASS()
class MANATOWER_API UFlaminaSpellTranslator : public USpellTranslator
{
	GENERATED_BODY()

public:
	virtual void CastSpell(FName Name, int Rotation = 0) override;

	UFUNCTION()
	void Fireball(int Rotation);	//Fireball function

	UFUNCTION()
	void JetFlame(int Rotation);	//JetFlame function

	UFUNCTION()
	void RestoreMana();		//Restore Mana

	UFUNCTION()
	void BigFireball(int Rotation);

	UFUNCTION()
	void Canister(int Rotation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> FireballClass = AFireballProjectile::StaticClass();	//FireballClass

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> JetFlameClass = AJetFlame::StaticClass();		//JetFlameClass

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> BigFireballClass = AFireballProjectile::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> SmallFireballClass = AFireballProjectile::StaticClass();
};