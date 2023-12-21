// Fill out your copyright notice in the Description page of Project Settings.


#include "EndRoom.h"

FString AEndRoom::GetNextLevel()
{
	return NextLevel;
}

void AEndRoom::SetNextLevel(FString nextLevel)
{
	NextLevel = nextLevel;
}
