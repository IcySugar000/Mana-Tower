// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomBase.h"
#include "PaperGroupedSpriteComponent.h"
#include "Components/SphereComponent.h"

ARoomBase::ARoomBase() 
{
	GroupedSpriteComponent = GetRenderComponent();

	// ¥¥Ω®ºÏ≤‚»¶
	DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Detect Sphere"));
	DetectSphere->SetSphereRadius((EdgeLength / 2.0f * FMath::Sqrt(3.0) - EdgeWidth) * 0.9);  // ƒ⁄«–‘≤ºÏ≤‚»¶
	DetectSphere->SetupAttachment(RootComponent);
}

void ARoomBase::SetCenterLocation(FVector location) 
{
	CenterLocation = location;
}

FVector ARoomBase::GetCenterLocation() 
{
	return CenterLocation;
}

void ARoomBase::BeginPlay()
{
	Super::BeginPlay();
}

void ARoomBase::SetEdge(TArray<int> doors)
{
	if (Edge)
	{
		auto NowTransform = FTransform();
		float bias = EdgeLength * FMath::Sin(FMath::DegreesToRadians(60.0)) - EdgeWidth / 2.0;
		FVector2D InitialPos = FVector2D(0.0, bias);

		for (int i = 0; i < 6; ++i)
		{
			auto newInitialPos = InitialPos.GetRotated(-30.0 - 60.0 * i);
			auto newTransform = NowTransform;
			newTransform.SetLocation(FVector(newInitialPos.X, 0.0, newInitialPos.Y));
			newTransform.SetRotation(FRotator(-30.0 - 60.0 * i, 0.0, 0.0).Quaternion());
			if(doors.Contains(i)) GroupedSpriteComponent->AddInstance(newTransform, EdgeOpen);
			else GroupedSpriteComponent->AddInstance(newTransform, Edge);
		}
	}
}

