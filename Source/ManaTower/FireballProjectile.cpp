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

	auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));
	if (capsule)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *capsule->GetName());
	FScriptDelegate DelegateOverlap;
	DelegateOverlap.BindUFunction(this, "OnHit");
	capsule->OnComponentBeginOverlap.Add(DelegateOverlap);
}

void AFireballProjectile::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	AddMovementInput(FVector(1, 0, 0), 100, false);

	LifeTime -= DeltaSeconds;
	if(LifeTime <= 0) {
		Destroy();
	}

	DetectTarget();
}

void AFireballProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	auto enemy = Cast<AEnemyBase>(OtherActor);
	if (enemy && SourcePlayer && DamageTypeClass) {
		UE_LOG(LogTemp, Warning, TEXT("HITTING"));
		UGameplayStatics::ApplyDamage(enemy, Damage, GetController(), SourcePlayer, DamageTypeClass);
		Destroy();
	}
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
