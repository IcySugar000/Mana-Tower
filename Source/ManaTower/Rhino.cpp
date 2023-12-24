// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ARhino::ARhino()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//���ŵĹ���
    MaxHealth = 80;
    Attack = 20;
    Speed = 1200;
    Defense = 0.3;//������ֵ�趨
    RushTime = MaxRushTime;

    auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));
    FScriptDelegate DelegateOverlap;
    DelegateOverlap.BindUFunction(this, "AttackPlayer");
    capsule->OnComponentHit.Add(DelegateOverlap);
}

void ARhino::BeginPlay()
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 80;//����������ֵ�������ô�����ô�͸ĳ�80

    MaxAttackCD = 4;
    AttackCD = 0;
    Health = MaxHealth;//������ֵΪ�������ֵ
    auto location = GetActorLocation();
    auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto playerLoaction = player->GetActorLocation();
    Direction = playerLoaction - location;
}

void ARhino::Tick(float deltaSeconds)
{
    Super::Tick(deltaSeconds);
    
    if (AttackCD <= 0 && RushTime>0) {//CDΪ0����RushTime��Ϊ0�����ֳ��״̬
        Direction.Normalize();
        AddMovementInput(Direction, Speed, false);
        RushTime -= deltaSeconds;
    }
    else if (AttackCD <= 0 && RushTime <= 0) {//CDΪ0����RushTimeΪ0���ոս�����̣�CD�ָ�Ϊ��󣬲���RushTimeҲ�ָ������
        RushTime = MaxRushTime;
        AttackCD = MaxAttackCD;
        auto location = GetActorLocation();
        auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
        auto playerLoaction = player->GetActorLocation();
        Direction = playerLoaction - location;
    }
    else if (AttackCD > 0 && RushTime <= 0) {
        RushTime = MaxRushTime;
        auto location = GetActorLocation();
        auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
        auto playerLoaction = player->GetActorLocation();
        Direction = playerLoaction - location;
        AttackCD -= deltaSeconds;
    }
    else {//���������������CD����٣���Ҫ������ǲ���ȷ����̷���
        auto location = GetActorLocation();
        auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
        auto playerLoaction = player->GetActorLocation();
        Direction = playerLoaction - location;
        AttackCD -= deltaSeconds;
    }
}

void ARhino::AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AttackCD>0 || RushTime<=0) return;
    
    if (Cast<APlayerBase>(OtherActor)) {
        auto enemy = Cast<APlayerBase>(OtherActor);
        float Damage = Attack;
        UGameplayStatics::ApplyDamage(enemy, Damage, GetController(), this, DamageTypeClass);
        UE_LOG(LogTemp, Warning, TEXT("HAHA, I ATTACK YOU!!!"));
        AttackCD = MaxAttackCD;
    }

    RushTime = MaxRushTime;
}