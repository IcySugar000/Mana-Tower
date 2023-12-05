// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellTranslator.generated.h"

USTRUCT(Blueprintable)
struct FMagicSpell {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<uint8> Activator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MANATOWER_API USpellTranslator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellTranslator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMagicSpell> MagicList;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Translate(TArray<uint8> InputActivator);
};
