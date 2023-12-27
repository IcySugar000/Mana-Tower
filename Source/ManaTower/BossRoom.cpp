// Fill out your copyright notice in the Description page of Project Settings.


#include "BossRoom.h"

void ABossRoom::BeginPlay() {
	Super::BeginPlay();

	SetEdge(TArray<int>());

	if(BossClass) {
		auto boss = GetWorld()->SpawnActor<AEnemyBase>(BossClass, GetCenterLocation(), GetActorRotation());
		boss->EnemyDie.AddUFunction(this, "OnBossDie");
	}
}

void ABossRoom::OnBossDie_Implementation(AEnemyBase* Enemy)
{
}
