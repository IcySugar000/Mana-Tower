// Fill out your copyright notice in the Description page of Project Settings.


#include "RadishRajesh.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ARadishRajesh::ARadishRajesh()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//活着的Boss
    MaxHealth = 300;
    Attack = 10;
    Speed = 1;
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
        MaxHealth = 300;//如果初始值设置错误，将boss的血量设为300

    Health = MaxHealth;//生命的初值为最大的生命值
}

void ARadishRajesh::Tick(float deltaSeconds)
{
    Super::Tick(deltaSeconds);

    MoveToPlayer();       //每一帧都要执行MoveToPlayer函数
}

void ARadishRajesh::AttackPlayer1(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AttackCD > 0.0) 
        return;

    if (!Cast<APlayerBase>(OtherActor)) 
        return;

    auto enemy = Cast<APlayerBase>(OtherActor);
    float Damage = Attack;
    UGameplayStatics::ApplyDamage(enemy, Damage, GetController(), this, DamageTypeClass);
    UE_LOG(LogTemp, Warning, TEXT("BOSS attack!")); //怪物boss近战攻击玩家的函数
    AttackCD = MaxAttackCD;
}

void ARadishRajesh::AttackPlayer2()
{

}

float ARadishRajesh::GetHealth()               //获取怪物boss的当前血量值
{
    return Health;
}

float ARadishRajesh::GetMaxHealth()            //获取怪物boss的最大血量值
{
    return MaxHealth;
}