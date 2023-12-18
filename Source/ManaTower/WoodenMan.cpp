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
    IsHadReportedDead = false;//���ŵĹ���
    MaxHealth = 80;
    Attack = 12;
    Speed = 0.8;
    Distance = 400;
    Defense = 0.02;//������ֵ�趨
    AttackCD = MaxAttackCD;
}

void AWoodenMan::BeginPlay()
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 80;//����������ֵ�������ô�����ô�͸ĳ�80

    Health = MaxHealth;//������ֵΪ�������ֵ
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
    }//��ֹbug
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
