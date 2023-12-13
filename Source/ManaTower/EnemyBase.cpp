// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

AEnemyBase::AEnemyBase() 
{
	FlipbookLibrary.FindOrAdd(FString("Idle"));
	FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//活着的怪物
    MaxHealth = 80;
    Defense = 0;
}

void AEnemyBase::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;//生命初值为最大生命值
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
    float RealDamageAmout = DamageAmount * (1.0 - Defense);//怪物受到的真实伤害
    Health -= RealDamageAmout;
    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);//报告收到的伤害
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