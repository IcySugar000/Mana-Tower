// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

AEnemyBase::AEnemyBase() 
{
	FlipbookLibrary.FindOrAdd(FString("Idle"));
	FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//���ŵĹ���
    MaxHealth = 80;
    Defense = 0;
}

void AEnemyBase::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;//������ֵΪ�������ֵ
}

void AEnemyBase::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	UpdateFlipbook();

	if (Health <= 0) {
		Die();
	}
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float RealDamageAmout = DamageAmount * (1.0 - Defense);//�����ܵ�����ʵ�˺�
    Health -= RealDamageAmout;
    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);//�����յ����˺�
    if(Health <= 0 && !IsDead) {
        Health = 0;
        Die();
    }
    return 0.0f;
}

void AEnemyBase::UpdateFlipbook()
{
    auto FlipbookComponent = GetSprite();
    auto velocity = GetVelocity();
    if (velocity.Size() > 0) {
        FlipbookComponent->SetFlipbook(FlipbookLibrary[FString("Move")]);
        if (velocity.X < 0) {
            SetActorScale3D(FVector(-1.0, 1.0, 1.0));
        }
        if (velocity.X > 0) {
            SetActorScale3D(FVector(1.0, 1.0, 1.0));
        }
    }
    else {
        FlipbookComponent->SetFlipbook(FlipbookLibrary[FString("Idle")]);
    }
}

void AEnemyBase::Die() {
    IsDead = true;
    if (!IsHadReportedDead)
    {
        IsHadReportedDead = true;
        UE_LOG(LogTemp, Warning, TEXT("AHHHH. I DIED"));
    }
       
}