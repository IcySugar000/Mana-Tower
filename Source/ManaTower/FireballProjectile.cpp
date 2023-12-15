// Fill out your copyright notice in the Description page of Project Settings.


#include "FireballProjectile.h"
#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"


AFireballProjectile::AFireballProjectile()
{
	LifeTime = MaxLifeTime;

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileComponent->InitialSpeed = Speed;
	ProjectileComponent->MaxSpeed = Speed;
	ProjectileComponent->ProjectileGravityScale = 0.0;
	ProjectileComponent->Velocity = FVector(0.0, 0.0, 1.0);
	ProjectileComponent->bRotationFollowsVelocity = true;
	ProjectileComponent->bIsHomingProjectile = true;
	ProjectileComponent->HomingAccelerationMagnitude = Acceleration;

	DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Detect Sphere"));
	DetectSphere->SetSphereRadius(DetectRange);
	DetectSphere->SetupAttachment(RootComponent);
}

void AFireballProjectile::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	// AddMovementInput(FVector(1, 0, 0), 100, false);

	LifeTime -= DeltaSeconds;
	if(LifeTime <= 0) {
		Destroy();
	}

	HitTarget();
	DetectTarget();
}

void AFireballProjectile::SetDamage(float newDamage) {
	Damage = newDamage;
}

void AFireballProjectile::SetSourcePlayer(APaperCharacter* player) {
	SourcePlayer = player;
}

void AFireballProjectile::DetectTarget() {
	TArray<AActor*> OverlapActors;
	DetectSphere->GetOverlappingActors(OverlapActors, AEnemyBase::StaticClass());

	for(auto actor: OverlapActors) {
		AEnemyBase* Enemy = Cast<AEnemyBase>(actor);
		if(Enemy) {
			ProjectileComponent->HomingTargetComponent = Enemy->GetComponentByClass<USceneComponent>();
		}
	}
}

void AFireballProjectile::HitTarget()
{
	auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));

	TArray<AActor*> OverlapActors;
	capsule->GetOverlappingActors(OverlapActors, AEnemyBase::StaticClass());

	if (!OverlapActors.IsEmpty()) {
		UGameplayStatics::ApplyDamage(OverlapActors[0], Damage, GetController(), SourcePlayer, DamageTypeClass);
		Destroy();
	}
}
