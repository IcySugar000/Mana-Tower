// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodenMan.h"
#include "WoodenManBullet.h"

AWoodenMan::AWoodenMan()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//活着的怪物
    MaxHealth = 80;
    Attack = 12;
    Speed = 0.8;
    Distance = 300;
    Defense = 0.02;//基本数值设定
   
}

void AWoodenMan::BeginPlay()
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 80;//如果最大生命值出现设置错误，那么就改成80

    Health = MaxHealth;//生命初值为最大生命值
}

void AWoodenMan::AttackPlayer()
{
    if (AttackCD > 0.0) return;

    //UE_LOG(LogTemp, Warning, TEXT("Bullet at Rotation: %d"), Rotation);

    auto myBullet = GetWorld()->SpawnActor<AWoodenManBullet>(BulletClass,
        GetOwner()->GetActorLocation(),
        FRotator(0.0, 0.0, 0.0));
    myBullet->SetSource(this);
    myBullet->SetDamage(Attack);
    
    AttackCD = MaxAttackCD;
}

