// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerBase.h"
#include "EnemyBase.h"


ABulletBase::ABulletBase()
{
	LifeTime = MaxLifeTime;

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileComponent->InitialSpeed = Speed;
	ProjectileComponent->MaxSpeed = Speed;
	ProjectileComponent->ProjectileGravityScale = 0.0;
	// ProjectileComponent->Velocity = FVector(0.0, 0.0, 1.0);
	// ProjectileComponent->bRotationFollowsVelocity = true;

	auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));
	FScriptDelegate DelegateHit;
	DelegateHit.BindUFunction(this, "OnHit");
	capsule->OnComponentHit.Add(DelegateHit);
}

void ABulletBase::BeginPlay()
{
	Super::BeginPlay();

	auto location = GetActorLocation();
	auto player = GetWorld()->GetFirstPlayerController();
	auto player2 = player->GetPawn();
	auto playerLoaction = player2->GetActorLocation();
	auto locationVec = playerLoaction - location;
	ProjectileComponent->Velocity = locationVec;
}

void ABulletBase::Tick(float DeltaSeconds)
{
	LifeTime -= DeltaSeconds;
	if (LifeTime <= 0) {
		Destroy();
	}
}


void ABulletBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsFromEnemy) {
		auto target = Cast<APlayerBase>(OtherActor);
		if (target && Source && DamageTypeClass) {
			UE_LOG(LogTemp, Warning, TEXT("HITTING"));
			UGameplayStatics::ApplyDamage(target, Damage, GetController(), Source, DamageTypeClass);
			Destroy();
		}
	}
	else {
		auto target = Cast<AEnemyBase>(OtherActor);
		if (target && Source && DamageTypeClass) {
			UE_LOG(LogTemp, Warning, TEXT("HITTING"));
			UGameplayStatics::ApplyDamage(target, Damage, GetController(), Source, DamageTypeClass);
			Destroy();
		}
	}

}

void ABulletBase::SetDamage(float newDamage)
{
	Damage = newDamage;
}

void ABulletBase::SetSource(APaperCharacter* source)
{
	Source = source;
}
