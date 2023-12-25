// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreRoom.h"

void AStoreRoom::GenerateItemList()
{
	AvailableItems.Empty();

	if(!StrToItem.IsEmpty()) {
		TArray<FString> keys;
		StrToItem.GetKeys(keys);
		for (int i = 0; i < ItemNum; ++i) {
			// AvailableItems.Emplace(AllItems[FMath::Rand() % AllItems.Num()]);
			AvailableItems.Emplace(keys[FMath::RandRange(0, keys.Num() - 1)]);
		}
	}
}
