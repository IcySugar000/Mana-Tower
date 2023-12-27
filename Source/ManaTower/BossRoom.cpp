// Fill out your copyright notice in the Description page of Project Settings.


#include "BossRoom.h"


void ABossRoom::BeginPlay() {
	Super::BeginPlay();

	SetEdge(TArray<int>());

	if(BossClass) {
		Boss = GetWorld()->SpawnActor<AEnemyBase>(BossClass, GetCenterLocation(), GetActorRotation());
		Boss->EnemyDie.AddUFunction(this, "OnBossDie");
		SetupHealthBar();
	}
}

void ABossRoom::OnBossDie_Implementation(AEnemyBase* Enemy)
{
}

void ABossRoom::SetupHealthBar_Implementation()
{
}
