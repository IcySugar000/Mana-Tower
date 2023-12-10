// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMap.h"

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

	// 初始化房间数组
	for(int i=0; i<Size * Size; ++i) {
		auto newRoom = GetWorld()->SpawnActor<ARoomBase>(RoomBase, GetActorLocation(), GetActorRotation());

		// 调整房间位置
		int roomXIndex = i / Size;
		int roomYIndex = i % Size;
		float length = 2 * newRoom->EdgeLength * FMath::Cos(FMath::DegreesToRadians(30.0));
		
		float roomX = (roomXIndex - roomYIndex) * length * FMath::Cos(FMath::DegreesToRadians(60.0));
		float roomY = (roomXIndex + roomYIndex) * length * FMath::Sin(FMath::DegreesToRadians(60.0));
		
		newRoom->SetActorLocation(FVector(roomX, 0.0, roomY));

		newRoom->SetEdge(doors[i]);

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

