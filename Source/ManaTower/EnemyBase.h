// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AEnemyBase : public APaperCharacter
{
	GENERATED_BODY()

private:
	int32 Health;
	bool IsDead;

	void UpdateFlipbook();

public:
	AEnemyBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Die();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UPaperFlipbook*> FlipbookLibrary;

};
