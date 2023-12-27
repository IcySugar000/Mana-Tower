// Fill out your copyright notice in the Description page of Project Settings.


#include "PinkBunny.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

APinkBunny::APinkBunny()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//活着的怪物
    MaxHealth = 100;
    Attack = 10;
    Speed = 0.003;
    Defense = 0.038;//基本数值设定
    //小彩蛋 

    auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));
    FScriptDelegate DelegateOverlap;
    DelegateOverlap.BindUFunction(this, "AttackPlayer");
    capsule->OnComponentHit.Add(DelegateOverlap);
}

void APinkBunny::BeginPlay()
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 100;//如果最大生命值出现设置错误，那么就改成80

    Health = MaxHealth;//生命初值为最大生命值
}

void APinkBunny::AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AttackCD > 0.0) 
        return;

    if (!Cast<APlayerBase>(OtherActor))
        return;

    auto enemy = Cast<APlayerBase>(OtherActor);
    float Damage = Attack;
    UGameplayStatics::ApplyDamage(enemy, Damage, GetController(), this, DamageTypeClass);
    UE_LOG(LogTemp, Warning, TEXT("HAHA, I ATTACK YOU!!!"));
    AttackCD = MaxAttackCD;
}

void APinkBunny::Tick(float deltaSeconds)
{
    Super::Tick(deltaSeconds);

    MoveToPlayer();
}