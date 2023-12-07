// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MazeGeneratorComponent.generated.h"


USTRUCT(Blueprintable)
struct FMazeNode {
	GENERATED_BODY()

	int32 x, y;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MANATOWER_API UMazeGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMazeGeneratorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray< TArray<bool> > IsVisited;
	TArray< TPair<FMazeNode, FMazeNode> > Paths;
	TArray< TPair<FMazeNode, FMazeNode> > AvailablePaths;
	const TArray< TPair<int32, int32> > Surrounds = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, -1}, {-1, 1} };

	bool IsInBound(int x, int y);
	void AddSurroundings(int x, int y);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetWorldSize(int WorldSize);
	void Generate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Size = 1;

	UPROPERTY()
	int32 AlreadyLinkedCount;
};
