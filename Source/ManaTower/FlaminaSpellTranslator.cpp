// Fill out your copyright notice in the Description page of Project Settings.


#include "FlaminaSpellTranslator.h"
#include "FireballProjectile.h"
#include "JetFlame.h"
#include "PlayerBase.h"

class APlayerBase;

void UFlaminaSpellTranslator::CastSpell(FName Name, int Rotation) 
{
	Super::CastSpell(Name, Rotation);

	if (Name == "Fireball")				//invoking Fireball(Rotation) Function
	{
		Fireball(Rotation);
	}
	else if(Name == "Restore Mana")		//invoking RestoreMana() Function
	{
		RestoreMana();
	}
	else if (Name == "JetFlame")
	{
		JetFlame(Rotation);				//invoking JetFlame(Rotation) Function
	}
	else if (Name == "Big Fireball") 
	{
		BigFireball(Rotation);
	}
	else if (Name == "Canister") 
	{
		Canister(Rotation);
	}
}

void UFlaminaSpellTranslator::Fireball(int Rotation) 
{
	//Output UE_LOG
	UE_LOG(LogTemp, Warning, TEXT("Fireball at Rotation: %d"), Rotation);
	//Cast PlayerBase
	auto player = Cast<APlayerBase>(GetOwner());
	//Rotation direction
	auto myFireball = GetWorld()->SpawnActor<AFireballProjectile>(FireballClass,
		GetOwner()->GetActorLocation(),
		FRotator(-60.0 * Rotation, 0.0, 0.0));
	//SetSourcePlayer function
	myFireball->SetSourcePlayer(GetTypedOuter<APaperCharacter>());
}

void UFlaminaSpellTranslator::RestoreMana() 
{
	//Output UE_LOG
	UE_LOG(LogTemp, Warning, TEXT("RestoreMana!"));
	//Cast PlayerBase
	auto player = Cast<APlayerBase>(GetOwner());

	if (player) 
	{
		player->RestoreMana(20);
	}
}

void UFlaminaSpellTranslator::BigFireball(int Rotation)
{
	//Cast PlayerBase
	auto player = Cast<APlayerBase>(GetOwner());
	//Rotation direction
	auto myFireball = GetWorld()->SpawnActor<AFireballProjectile>(BigFireballClass,
		GetOwner()->GetActorLocation(),
		FRotator(-60.0 * Rotation, 0.0, 0.0));
	//SetSourcePlayer function
	myFireball->SetSourcePlayer(GetTypedOuter<APaperCharacter>());
}

void UFlaminaSpellTranslator::Canister(int Rotation)
{
	//Cast PlayerBase
	auto player = Cast<APlayerBase>(GetOwner());
	//Rotation direction
	for(int i=0; i<10; ++i) {
		auto myFireball = GetWorld()->SpawnActor<AFireballProjectile>(SmallFireballClass,
			GetOwner()->GetActorLocation(),
			FRotator(-60.0 * Rotation + FMath::RandRange(-30.0, 30.0), 0.0, 0.0));
		//SetSourcePlayer function
		if (myFireball) 
			myFireball->SetSourcePlayer(player);
		else 
			UE_LOG(LogTemp, Warning, TEXT("NO fireball"));
	}
}

void UFlaminaSpellTranslator::JetFlame(int Rotation) 
{
	//Output UE_LOG
	UE_LOG(LogTemp, Warning, TEXT("JetFlame attck!"), Rotation);
	//Cast PlayerBase
	auto player = Cast<APlayerBase>(GetOwner());
	//Rotation direction
	auto myJetFlame = GetWorld()->SpawnActor<AJetFlame>(JetFlameClass,
		GetOwner()->GetActorLocation(),
		FRotator(-60.0 * Rotation, 0.0, 0.0));
	//SetSourcePlayer function
	if(myJetFlame)
		myJetFlame->SetSourcePlayer(GetTypedOuter<APaperCharacter>());

}
