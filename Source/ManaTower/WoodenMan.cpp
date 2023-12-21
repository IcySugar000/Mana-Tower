// Fill out your copyright notice in the Description page of Project Settings.

#include <ctime>
#include <random>
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
    std::uniform_real_distribution<float> u(0.5, 1.5);
    std::default_random_engine e(time(NULL));
    AttackCD = u(e) * MaxAttackCD;
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

    MoveToPlayer();
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

