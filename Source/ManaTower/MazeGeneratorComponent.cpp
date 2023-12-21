// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGeneratorComponent.h"

#include "LevelMap.h"
#include "Chaos/ChaosPerfTest.h"

// Sets default values for this component's properties
UMazeGeneratorComponent::UMazeGeneratorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMazeGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


bool UMazeGeneratorComponent::IsInBound(int x, int y)
{
	return x <= Size-1 && y <= Size-1 && x >= 0 && y >= 0;
}

void UMazeGeneratorComponent::AddSurroundings(int x, int y)
{
	for (auto move : Surrounds) {
		int32 dx = move.Get<0>(), dy = move.Get<1>();
		if (IsInBound(x + dx, y + dy) && !IsVisited[x + dx][y + dy]) {
			FMazeNode tmp1, tmp2;
			tmp1.x = x;
			tmp1.y = y;
			tmp2.x = x + dx;
			tmp2.y = y + dy;
			AvailablePaths.Emplace(TPair<FMazeNode, FMazeNode>(tmp1, tmp2));
		}
	}
}

// Called every frame
void UMazeGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

TTuple<int32, int32, int32> UMazeGeneratorComponent::GetEndRoomPosition() {
	// BFS，取最远的房间
	struct Node {
		int x, y;
		int dis;  // 记录和起点的距离

		Node() {
			x = -1;
			y = -1;
			dis = -1;
		}

		Node(int ix, int iy, int idis) {
			x = ix;
			y = iy;
			dis = idis;
		}
	};

	Node maxNode;

	using namespace std;

	TArray< TArray<bool> > book;
	TArray<bool> tmp;
	tmp.Init(false, Size);
	book.Init(tmp, Size);

	TArray < TArray<bool> > paths;
	TArray<bool> tmpPath;
	tmpPath.Init(false, Size* Size);
	paths.Init(tmpPath, Size* Size);
	for(auto p: Paths) {
		paths[p.Get<0>().x * Size + p.Get<0>().y][p.Get<1>().x * Size + p.Get<1>().y] = true;
	}

	queue<Node> q;
	q.push(Node(0, 0, 0));
	book[0][0] = true;

	while(!q.empty()) {
		auto node = q.front();
		q.pop();

		for(auto move: Surrounds) {
			int xx = node.x + move.Get<0>();
			int yy = node.y + move.Get<1>();
			if(IsInBound(xx, yy) && !book[xx][yy] && paths[node.x * Size + node.y][xx * Size + yy]) {
				book[xx][yy] = true;
				Node newNode(xx, yy, node.dis + 1);
				q.push(newNode);
				if (newNode.dis > maxNode.dis) maxNode = newNode;
			}
		}
	}

	auto result = MakeTuple(maxNode.x, maxNode.y, maxNode.dis);
	return result;
}

void UMazeGeneratorComponent::SetWorldSize(int32 WorldSize)
{
	Size = WorldSize;
}

void UMazeGeneratorComponent::Generate()
{
	Size = Cast<ALevelMap>(GetOuter())->Size;

	Paths.Empty();
	IsVisited.Empty();
	AvailablePaths.Empty();
	for (int i = 0; i < Size; ++i) {
		TArray<bool> tmp;
		for (int j = 0; j < Size; ++j) tmp.Emplace(false);
		IsVisited.Emplace(tmp);
	}

	AvailablePaths.Append(0, 0);
	IsVisited[0][0] = true;
	AddSurroundings(0, 0);
	AlreadyLinkedCount = 1;

	while (AlreadyLinkedCount < Size * Size) {
		int chosenIndex = FMath::RandRange(0, AvailablePaths.Num() - 1);
		auto path = AvailablePaths[chosenIndex];
		AvailablePaths.RemoveAt(chosenIndex);

		if (!IsVisited[path.Get<1>().x][path.Get<1>().y]) {
			Paths.Emplace(path);
			IsVisited[path.Get<1>().x][path.Get<1>().y] = true;
			AddSurroundings(path.Get<1>().x, path.Get<1>().y);
			++AlreadyLinkedCount;
		}
	}

	for (auto p : Paths) {
		UE_LOG(LogTemp, Warning, TEXT("%d %d %d %d"), p.Get<0>().x, p.Get<0>().y, p.Get<1>().x, p.Get<1>().y);
	}
}

TArray< TPair<FMazeNode, FMazeNode> > UMazeGeneratorComponent::GetResult() {
	return Paths;
}

