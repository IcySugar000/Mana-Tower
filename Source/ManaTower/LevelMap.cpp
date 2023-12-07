// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMap.h"

// Sets default values
ALevelMap::ALevelMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MazeGenerator = CreateDefaultSubobject<UMazeGeneratorComponent>(TEXT("Maze Generator"));
	MazeGenerator->SetWorldSize(3);
	MazeGenerator->Generate();

}

// Called when the game starts or when spawned
void ALevelMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

