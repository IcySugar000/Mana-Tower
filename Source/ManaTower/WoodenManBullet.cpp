// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodenManBullet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerBase.h"
#include "EnemyBase.h"

void AWoodenManBullet::BeginPlay()
{
	Super::BeginPlay();

	MaxLifeTime = 3;
	Speed = 400;
	LifeTime = MaxLifeTime;
	ProjectileComponent->InitialSpeed = Speed;
	ProjectileComponent->MaxSpeed = Speed;
	
	auto location = GetActorLocation();
	auto player = GetWorld()->GetFirstPlayerController();
	auto player2 = player->GetPawn();
	auto playerLoaction = player2->GetActorLocation();
	auto locationVec = playerLoaction - location;
	ProjectileComponent->Velocity = locationVec;
}
