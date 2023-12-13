// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMap.h"

#include "EndRoom.h"

// Sets default values
ALevelMap::ALevelMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MazeGenerator = CreateDefaultSubobject<UMazeGeneratorComponent>(TEXT("Maze Generator"));
	MazeGenerator->SetWorldSize(Size);
	MazeGenerator->Generate();

}

// Called when the game starts or when spawned
void ALevelMap::BeginPlay()
{
	Super::BeginPlay();

	TArray < TArray<int> > doors;
	for (int i = 0; i < Size * Size; ++i) doors.Emplace(TArray<int>());
	auto Paths = MazeGenerator->GetResult();
	for(auto path: Paths) {
		auto node1 = path.Get<0>();
		auto node2 = path.Get<1>();
		for(int i=0; i<6; ++i) {
			auto move = Surrounds[i];
			auto moveX = move.Get<0>();
			auto moveY = move.Get<1>();
			if(node1.x+moveX == node2.x && node1.y+moveY == node2.y) {
				doors[node1.x * Size + node1.y].Emplace(i);
				if(i < 3) doors[node2.x * Size + node2.y].Emplace(i+3);
				else doors[node2.x * Size + node2.y].Emplace(i-3);
			}
		}
	}

	auto EndPos = MazeGenerator->GetEndRoomPosition();
	UE_LOG(LogTemp, Warning, TEXT("END: %d, %d"), EndPos.Get<0>(), EndPos.Get<1>());

	// 初始化房间数组
	for(int i=0; i<Size * Size; ++i) {
		int roomXIndex = i / Size;
		int roomYIndex = i % Size;
		ARoomBase* newRoom;

		FString type = "";
		if(roomXIndex == EndPos.Get<0>() && roomYIndex == EndPos.Get<1>()) {  // 作为终点，设置为EndRoom
			newRoom = GetWorld()->SpawnActor<ARoomBase>(EndRoom, GetActorLocation(), GetActorRotation());
			type = "End";
		}
		else if(roomXIndex == 0 && roomYIndex == 0) {  // 作为起点，设置为基类Room
			newRoom = GetWorld()->SpawnActor<ARoomBase>(RoomBase, GetActorLocation(), GetActorRotation());
			type = "Start";
		}
		else {  // 其他房间为生成怪物的房间
			newRoom = GetWorld()->SpawnActor<ARoomBase>(EnemyRoom, GetActorLocation(), GetActorRotation());
			type = "Enemy";
		}

		// 调整房间位置
		float length = 2 * newRoom->EdgeLength * FMath::Cos(FMath::DegreesToRadians(30.0));
		
		float roomX = (roomXIndex - roomYIndex) * length * FMath::Cos(FMath::DegreesToRadians(60.0));
		float roomY = (roomXIndex + roomYIndex) * length * FMath::Sin(FMath::DegreesToRadians(60.0));
		
		newRoom->SetActorLocation(FVector(roomX, 0.0, roomY));
		newRoom->SetCenterLocation(FVector(roomX, 0.0, roomY));

		newRoom->SetEdge(doors[i]);

		// 一些后续的生成
		if(type == "Enemy") {
			auto enemyRoom = Cast<AEnemyRoom>(newRoom);
			enemyRoom->SetEnemyTypes(EnemyTypes);
			enemyRoom->SpawnEnemy();
		}

		RoomArray.Emplace(newRoom);
	}

}

bool ALevelMap::IsInBound(int x, int y) {
	return x >= 0 && x < Size && y >= 0 && y < Size;
}

ARoomBase* ALevelMap::GetRoomInArray(int x, int y) {
	if (!IsInBound(x, y)) return nullptr;
	return RoomArray[x * Size + y];
}

// Called every frame
void ALevelMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

