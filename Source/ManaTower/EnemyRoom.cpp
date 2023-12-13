// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRoom.h"

#include "PlayerBase.h"

void AEnemyRoom::BeginPlay() {
	Super::BeginPlay();

	DelegateEnter.BindUFunction(this, "OnEnter");
	DetectSphere->OnComponentBeginOverlap.Add(DelegateEnter);
}

void AEnemyRoom::SetEnemyTypes(TArray<TSubclassOf<AEnemyBase>> types) {
	EnemyTypes = types;
}

void AEnemyRoom::SpawnEnemy() {
	UE_LOG(LogTemp, Warning, TEXT("SPAWNING ENEMIES"));
	if (EnemyTypes.IsEmpty()) EnemyTypes.Emplace(AEnemyBase::StaticClass());  // �������ɹ������࣬��Ĭ������Base

	auto spawnRange = EdgeLength / 2.0f * FMath::Sqrt(3.0);  // ���ɹ��ﷶΧ��Ϊ���������������Բ

	for (int i = 0; i < SpawnNum; ++i) {
		auto randIndex = FMath::RandRange(0, EnemyTypes.Num() - 1);

		AEnemyBase* newEnemy = NULL;
		while(newEnemy == NULL) {
			// �����������ƫ��
			auto location = GetCenterLocation();
			auto radius = FMath::RandRange(0.0, spawnRange);
			auto radian = FMath::RandRange(0.0, FMath::DegreesToRadians(360.0));
			location.X += radius * FMath::Cos(radian);
			location.Z += radius * FMath::Sin(radian);
		
			newEnemy = GetWorld()->SpawnActor<AEnemyBase>(EnemyTypes[randIndex], location, GetActorRotation());
		}
	}
}

void AEnemyRoom::OnEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (IsHadEntered) return;

	if (Cast<APlayerBase>(OtherActor)) {
		IsHadEntered = true;
		SpawnEnemy();
	}
}
