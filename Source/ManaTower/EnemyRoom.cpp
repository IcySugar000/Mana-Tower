// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRoom.h"

void AEnemyRoom::SetEnemyTypes(TArray<TSubclassOf<AEnemyBase>> types) {
	EnemyTypes = types;
}

void AEnemyRoom::SpawnEnemy() {
	if (EnemyTypes.IsEmpty()) EnemyTypes.Emplace(AEnemyBase::StaticClass());  // 若无生成怪物种类，则默认生成Base

	auto spawnRange = EdgeLength / 2.0f * FMath::Sqrt(3.0);  // 生成怪物范围，为房间的六边形内切圆

	for (int i = 0; i < SpawnNum; ++i) {
		auto randIndex = FMath::RandRange(0, EnemyTypes.Num() - 1);

		AEnemyBase* newEnemy = NULL;
		while(newEnemy == NULL) {
			// 设置随机坐标偏移
			auto location = GetCenterLocation();
			auto radius = FMath::RandRange(0.0, spawnRange);
			auto radian = FMath::RandRange(0.0, FMath::DegreesToRadians(360.0));
			location.X += radius * FMath::Cos(radian);
			location.Z += radius * FMath::Sin(radian);

			newEnemy = GetWorld()->SpawnActor<AEnemyBase>(EnemyTypes[randIndex], location, GetActorRotation());
		}
		EnemyInRoom.Emplace(newEnemy);
	}
}
