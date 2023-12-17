// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodenMan.h"
#include "WoodenManBullet.h"

AWoodenMan::AWoodenMan()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//���ŵĹ���
    MaxHealth = 80;
    Attack = 12;
    Speed = 0.8;
    Distance = 300;
    Defense = 0.02;//������ֵ�趨
   
}

void AWoodenMan::BeginPlay()
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 80;//����������ֵ�������ô�����ô�͸ĳ�80

    Health = MaxHealth;//������ֵΪ�������ֵ
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

