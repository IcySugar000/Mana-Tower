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
    IsHadReportedDead = false;//���ŵ�Boss
    MaxHealth = 300;
    Attack = 10;
    Speed = 1;
    //һЩBoss�Ļ������ܵ��趨

    auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));
    FScriptDelegate DelegateOverlap;
    DelegateOverlap.BindUFunction(this, "AttackPlayer");
    capsule->OnComponentHit.Add(DelegateOverlap);
}

void ARadishRajesh::BeginPlay()//��ʼ��Ϸ��BOSS��ʼ
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 300;//�����ʼֵ���ô��󣬽�boss��Ѫ����Ϊ300

    Health = MaxHealth;//�����ĳ�ֵΪ��������ֵ
}

void ARadishRajesh::Tick(float deltaSeconds)
{
    Super::Tick(deltaSeconds);

    MoveToPlayer();       //ÿһ֡��Ҫִ��MoveToPlayer����
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
    UE_LOG(LogTemp, Warning, TEXT("BOSS attack!")); //����boss��ս������ҵĺ���
    AttackCD = MaxAttackCD;
}

void ARadishRajesh::AttackPlayer2()
{

}

float ARadishRajesh::GetHealth()               //��ȡ����boss�ĵ�ǰѪ��ֵ
{
    return Health;
}

float ARadishRajesh::GetMaxHealth()            //��ȡ����boss�����Ѫ��ֵ
{
    return MaxHealth;
}