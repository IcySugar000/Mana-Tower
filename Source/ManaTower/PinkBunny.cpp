// Fill out your copyright notice in the Description page of Project Settings.


#include "PinkBunny.h"

APinkBunny::APinkBunny()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//���ŵĹ���
    MaxHealth = 100;
    Attack = 10;
    Defense = 0.038;//������ֵ�趨
    //С�ʵ� 
}

void APinkBunny::BeginPlay()
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 100;//����������ֵ�������ô�����ô�͸ĳ�80

    Health = MaxHealth;//������ֵΪ�������ֵ
}
