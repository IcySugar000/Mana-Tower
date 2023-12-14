// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire_DamageType.h"
#include "PaperCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JetFlame.generated.h"

/**
 * 
 */
UCLASS()
class MANATOWER_API AJetFlame : public APaperCharacter
{
	GENERATED_BODY()

private:

	float LifeTime;						//��������ʱ��
	float Damage = 50;					//������ɵ��˺�
	APaperCharacter* SourcePlayer;		//�������˺���Դ��Ĭ��Ϊ��ң�

public:

	AJetFlame();						//���캯��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	float MaxLifeTime = 2;				//���Ĵ���ʱ��

};
