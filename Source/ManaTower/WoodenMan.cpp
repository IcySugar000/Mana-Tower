// Fill out your copyright notice in the Description page of Project Settings.

#include <time.h>
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
  
}

void AWoodenMan::BeginPlay()
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 80;//����������ֵ�������ô�����ô�͸ĳ�80

    AttackCD = FMath::RandRange(0.5, 1.5) * MaxAttackCD;//��ʼCD��0.5��1.5�����CD�м䣬�������

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
    if (AttackCD <= 0.0)
    {
        auto myBullet = GetWorld()->SpawnActor<AWoodenManBullet>(BulletClass,
            GetActorLocation(),
            FRotator(0.0, 0.0, 0.0));
        if (myBullet) {//��ֹbug
            myBullet->SetSource(this);
            myBullet->SetDamage(Attack);
        }
        AttackCD = MaxAttackCD;
    }
    
}

