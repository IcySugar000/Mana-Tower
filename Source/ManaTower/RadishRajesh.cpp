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

void ARadishRajesh::BeginPlay()
{

}