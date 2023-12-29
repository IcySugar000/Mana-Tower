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

void AFireballProjectile::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);
	// AddMovementInput(FVector(1, 0, 0), 100, false);

	LifeTime -= DeltaSeconds;
	if(LifeTime <= 0) 
	{
		Destroy();
	}

	HitTarget();
	DetectTarget();
}

void AFireballProjectile::SetDamage(float newDamage)
{
	Damage = newDamage;
}

void AFireballProjectile::SetSourcePlayer(APaperCharacter* player) 
{
	SourcePlayer = player;
}

void AFireballProjectile::DetectTarget() 
{
	TArray<AActor*> OverlapActors;
	DetectSphere->GetOverlappingActors(OverlapActors, AEnemyBase::StaticClass());

	for(auto actor: OverlapActors) 
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(actor);
		if(Enemy)
		{
			ProjectileComponent->HomingTargetComponent = Enemy->GetComponentByClass<USceneComponent>();
		}
	}
}

void AFireballProjectile::HitTarget()
{
	auto capsule = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));	//创建胶囊（即每一个物体周围都会有的范围标志物品）

	TArray<AActor*> OverlapActors;			//数组：用来存放和该伤害有交集的物品
	capsule->GetOverlappingActors(OverlapActors, AEnemyBase::StaticClass());	//这个有交集的物品集合是EnemyBase（即敌人）

	//如果这个交集存放的数组（敌人）不为空，即打到了敌人
	if (!OverlapActors.IsEmpty()) 
	{
		//由于火球是只造成最先碰到的敌人的伤害的，所以OverlapActors[0]表示第一个受到伤害的敌人，给其造成伤害
		float realDamage = UGameplayStatics::ApplyDamage(OverlapActors[0], Damage, GetController(), SourcePlayer, DamageTypeClass);
		auto player = Cast<APlayerBase>(SourcePlayer);
		if (player) player->RestoreHealth(realDamage * 0.05);
		Destroy();
	}
	
}
