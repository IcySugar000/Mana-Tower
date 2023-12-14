// Fill out your copyright notice in the Description page of Project Settings.


#include "JetFlame.h"
#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AJetFlame::AJetFlame()					//火柱的生成
{
	LifeTime = MaxLifeTime;				//生存周期默认为最大的生存时间
}




