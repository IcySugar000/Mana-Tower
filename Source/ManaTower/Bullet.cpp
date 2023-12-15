// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "EnemyBase.h"
#include "PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ABullet::ABullet()
{
	LifeTime = MaxLifeTime;

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileComponent->InitialSpeed = Speed;
	ProjectileComponent->MaxSpeed = Speed;
	ProjectileComponent->ProjectileGravityScale = 0.0;
	auto location = GetActorLocation();
	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto playerLoaction = player->GetActorLocation();
	auto locationVec = playerLoaction - location;
	ProjectileComponent->Velocity = locationVec;
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

void ABullet::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	auto enemy = Cast<APlayerBase>(OtherActor);
	if (enemy && SourcePlayer && DamageTypeClass) {
		UE_LOG(LogTemp, Warning, TEXT("BULLET HITTING"));
		UGameplayStatics::ApplyDamage(enemy, Damage, GetController(), SourcePlayer, DamageTypeClass);
		Destroy();
	}
}


void ABullet::DetectTarget() {
	
}
