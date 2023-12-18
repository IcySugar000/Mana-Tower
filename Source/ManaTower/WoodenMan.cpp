// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodenMan.h"
#include "WoodenManBullet.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AWoodenMan::AWoodenMan()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//活着的怪物
    MaxHealth = 80;
    Attack = 12;
    Speed = 0.8;
    Distance = 400;
    Defense = 0.02;//基本数值设定
    AttackCD = MaxAttackCD;
}

void AWoodenMan::BeginPlay()
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 80;//如果最大生命值出现设置错误，那么就改成80

    Health = MaxHealth;//生命初值为最大生命值
}

void AWoodenMan::Tick(float deltaSeconds)
{
    Super::Tick(deltaSeconds);

    AttackPlayer();
}

void AWoodenMan::AttackPlayer()
{
    if (AttackCD > 0.0) return;

    auto myBullet = GetWorld()->SpawnActor<AWoodenManBullet>(BulletClass,
        GetActorLocation(),
        FRotator(0.0, 0.0, 0.0));
    if (myBullet){
        myBullet->SetSource(this);
        myBullet->SetDamage(Attack);
    }//防止bug
    AttackCD = MaxAttackCD;
}

void AWoodenMan::MoveToPlayer()
{
    // AttackPlayer();
    auto location = GetActorLocation();
    auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto playerLoaction = player->GetActorLocation();
    auto locationVec = playerLoaction - location;
    if (locationVec.X * locationVec.X + locationVec.Y * locationVec.Y + locationVec.Z * locationVec.Z > Distance * Distance) {
        // if (player) UE_LOG(LogTemp, Warning, TEXT("%lf %lf %lf"), locationVec.X, locationVec.Y, locationVec.Z);
        AddMovementInput(locationVec, Speed, false);
    }
    
}
