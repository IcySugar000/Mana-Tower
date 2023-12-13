// Fill out your copyright notice in the Description page of Project Settings.


#include "PinkBunny.h"

APinkBunny::APinkBunny()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//活着的怪物
    MaxHealth = 100;
    Attack = 10;
    Defense = 0.038;//基本数值设定
    //小彩蛋 
}

void APinkBunny::BeginPlay()
{
    Super::BeginPlay();

    if (MaxHealth <= 0)
        MaxHealth = 100;//如果最大生命值出现设置错误，那么就改成80

    Health = MaxHealth;//生命初值为最大生命值
}
