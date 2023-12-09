// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FireballProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AFireballProjectile : public APaperCharacter
{
	GENERATED_BODY()
	
private:
	float LifeTime;
	void DetectTarget();

public:
	AFireballProjectile();
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> DetectSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLifeTime = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectRange = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Acceleration = 10000.0;
};
