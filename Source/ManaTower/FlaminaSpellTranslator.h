// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireballProjectile.h"
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
	void Fireball(int Rotation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APaperCharacter> FireballClass = AFireballProjectile::StaticClass();
};