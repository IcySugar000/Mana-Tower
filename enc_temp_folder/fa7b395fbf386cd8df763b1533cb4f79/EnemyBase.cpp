// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"


AEnemyBase::AEnemyBase() 
{
	FlipbookLibrary.FindOrAdd(FString("Idle"));
	FlipbookLibrary.FindOrAdd(FString("Move"));

    IsDead = false;
    IsHadReportedDead = false;//活着的怪物
    MaxHealth = 80;
    Speed = 1;
    Attack = 10.0;
    Defense = 0;
    MaxAttackCD = 3;
    AttackCD = 0;

    auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));
    FScriptDelegate DelegateOverlap;
    DelegateOverlap.BindUFunction(this, "AttackPlayer");
    capsule->OnComponentHit.Add(DelegateOverlap);
}

void AEnemyBase::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;//生命初值为最大生命值
}

void AEnemyBase::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	UpdateFlipbook();

    MoveToPlayer();

	if (Health <= 0) {
		Die();
	}

    if (AttackCD > 0.0) 
        AttackCD -= DeltaSeconds;

}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float RealDamageAmout = DamageAmount * (1.0 - Defense);//怪物受到的真实伤害
    Health -= RealDamageAmout;
    if (Health <= 0 && !IsDead) {
        Health = 0;
        Die();
    }
    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);//报告收到的伤害
    
    return 0.0f;
}

void AEnemyBase::UpdateFlipbook()
{
    auto FlipbookComponent = GetSprite();
    auto velocity = GetVelocity();
    if (velocity.Size() > 0) {
        FlipbookComponent->SetFlipbook(FlipbookLibrary[FString("Move")]);
        if (velocity.X < 0) {
            SetActorScale3D(FVector(1.0, 1.0, 1.0));
        }
        if (velocity.X > 0) {
            SetActorScale3D(FVector(-1.0, 1.0, 1.0));
        }
    }
    else {
        FlipbookComponent->SetFlipbook(FlipbookLibrary[FString("Idle")]);
    }
}

void AEnemyBase::Die() 
{
    IsDead = true;
    if (!IsHadReportedDead){
        IsHadReportedDead = true;
        UE_LOG(LogTemp, Warning, TEXT("AHHHH. I DIED"));
    }

    EnemyDie.Broadcast(this);  // 广播死亡事件给绑定的函数

    Destroy();
}

void AEnemyBase::MoveToPlayer()
{
    auto location = GetActorLocation();
    auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto playerLoaction = player->GetActorLocation();
    auto locationVec = playerLoaction - location;
    if (locationVec.X * locationVec.X + locationVec.Y * locationVec.Y + locationVec.Z * locationVec.Z > Distance * Distance) {
        if (player) UE_LOG(LogTemp, Warning, TEXT("%lf %lf %lf"), locationVec.X, locationVec.Y, locationVec.Z);
        AddMovementInput(locationVec, Speed, false);
    }
}

void AEnemyBase::AttackPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AttackCD > 0.0) return;

    if (!Cast<APlayerBase>(OtherActor)) return;
    
    auto enemy = Cast<APlayerBase>(OtherActor);
    float Damage = Attack;
    UGameplayStatics::ApplyDamage(enemy, Damage, GetController(), this, DamageTypeClass);
    UE_LOG(LogTemp, Warning, TEXT("HAHA, I ATTACK YOU!!!"));
    AttackCD = MaxAttackCD;
}

