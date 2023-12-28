// Fill out your copyright notice in the Description page of Project Settings.

#include "RadishRajesh.h"
#include "PlayerBase.h"
#include "WoodenManBullet.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ARadishRajesh::ARadishRajesh()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//活着的怪物
    MaxHealth = 600;
    Defense = 0.3;
    BossState = 0;
    AttackCD = 0.1;
    MaxAttackCD = 1.2;
    RecordTime = 0;
    //一些Boss的基本功能的设定

    auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));
    FScriptDelegate DelegateOverlap;
    DelegateOverlap.BindUFunction(this, "AttackPlayer");
    capsule->OnComponentHit.Add(DelegateOverlap);
}

void ARadishRajesh::BeginPlay()//开始游戏的BOSS初始
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 600;//如果初始值设置错误，将boss的血量设为600

    Health = MaxHealth;//生命的初值为最大的生命值
}

void ARadishRajesh::Tick(float deltaSeconds)
{
    Super::Tick(deltaSeconds);

    WhichState();

    RecordTime += deltaSeconds;

    MoveToPlayer();//每一帧都要执行MoveToPlayer函数
}

void ARadishRajesh::MoveToPlayer()//Boss的移动函数，移动的方向为向玩家方向
{
    if (BossState == 0)
        return;
    auto location = GetActorLocation();
    auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto playerLoaction = player->GetActorLocation();
    auto locationVec = playerLoaction - location;
    if (BossState == 1)
    {
        AddMovementInput(locationVec, StateSpeed[1], false);
    }
    else if (BossState == 3)
    {
        if (RecordTime < 2 && RecordTime > 0.1)
        {
            Direction.Normalize();
            AddMovementInput(Direction, StateSpeed[3], false);
            //BossState = 3;
        }
        else
        {
            Direction = playerLoaction - location;
        }
    }
    //木头人模式的攻击被整合在Move中
    else if (IsHaveShort <= 5 && RecordTime >= IsHaveShort)
    {
        auto myBullet = GetWorld()->SpawnActor<AWoodenManBullet>(BulletClass,
            GetActorLocation(),
            FRotator(0.0, 0.0, 0.0));
        if (myBullet) // 防止bug
        {
            myBullet->SetSource(this);
            myBullet->SetDamage(FMath::RandRange(8, 16));
        }
        IsHaveShort += 0.13;
    }
}

void ARadishRajesh::WhichState()
{
   // UE_LOG(LogTemp, Warning, TEXT("%f"), RecordTime);
    //UE_LOG(LogTemp, Warning, TEXT("%d"), BossState);
    if (RecordTime >= 3 && BossState == 0)
    {
        BossState = FMath::RandRange(1,3);
        IsHaveShort = 0.2;
        AttackCD = 0.1;
        RecordTime = 0;
    }
    else if ((RecordTime >= 5 && BossState == 1) || (RecordTime >= 5 && BossState == 2) || (RecordTime >= 2 && BossState == 3))
    {
        RecordTime = 0;
        BossState = 0;
    }
        
}

void ARadishRajesh::AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AttackCD > 0.0)
        return;

    if (!Cast<APlayerBase>(OtherActor))
        return;

    auto enemy = Cast<APlayerBase>(OtherActor);

    float Damage = 0;
    if (BossState == 1)
        Damage = FMath::RandRange(15, 31);
    else
        Damage = FMath::RandRange(20, 41);

    UGameplayStatics::ApplyDamage(enemy, Damage, GetController(), this, DamageTypeClass);
    UE_LOG(LogTemp, Warning, TEXT("HAHA, BOSS ATTACK YOU!!!"));
    AttackCD = MaxAttackCD;
}
