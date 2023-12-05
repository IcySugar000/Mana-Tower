// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellTranslator.h"

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

void USpellTranslator::Translate(TArray<uint8> InputActivator) {
	UE_LOG(LogTemp, Warning, TEXT("Translating..."));
	for(auto digit: InputActivator) UE_LOG(LogTemp, Warning, TEXT("%d"), digit);
	if(MagicList.IsEmpty()) UE_LOG(LogTemp, Warning, TEXT("Empty List!"));
	for(auto spell: MagicList) {
		for (auto digit : spell.Activator) UE_LOG(LogTemp, Warning, TEXT("spell %d"), digit);
		if(spell.Activator == InputActivator) {
			UE_LOG(LogTemp, Warning, TEXT("%s"), *spell.Name.ToString());
		}
	}
}

