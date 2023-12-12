// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

#include "MagicCircle.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

APlayerBase::APlayerBase()
{
    FlipbookLibrary.FindOrAdd(FString("Idle"));
    FlipbookLibrary.FindOrAdd(FString("Run"));

    Translator = CreateDefaultSubobject<USpellTranslator>(TEXT("Spell Translator"));
    Translator->MyCharacter = this;

    // if(Translator) UE_LOG(LogTemp, Warning, TEXT("Yes Translator!"));
}

void APlayerBase::BeginPlay()
{
    Super::BeginPlay();

    Controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);

    Controller->SetShowMouseCursor(true);

    MyMagicCircle = CreateWidget<UUserWidget>(Controller, MagicCircleClass);
    if (MyMagicCircle) MyMagicCircle->AddToViewport();                      //魔法阵的AddToViewport

    MyHealthbar= CreateWidget<UUserWidget>(Controller, HealthBarClass);  //血条的AddToViewport
    if (MyHealthbar) MyHealthbar->AddToViewport();
    
    auto tempCircle = Cast<UMagicCircle>(MyMagicCircle);
    Translator->SetButtonNum(tempCircle->ButtonMap.Num());
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(InputComponent);

    InputComponent->BindAxis(TEXT("Move_Right"), this, &APlayerBase::MoveRight);
    InputComponent->BindAxis(TEXT("Move_Up"), this, &APlayerBase::MoveUp);
}

float APlayerBase::GetHealth() {
    return Health;
}

float APlayerBase::GetMaxHealth() {
    return MaxHealth;
}

void APlayerBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UpdateFlipbook();
}

void APlayerBase::CastSpell(TArray<uint8> ExistLines) {
    if (Translator) {
        Translator->Translate(ExistLines);
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("No Translator!"));
    }
}

void APlayerBase::MoveRight(float ScaleValue)
{
    AddMovementInput(FVector(1, 0, 0), ScaleValue, false);
    if(ScaleValue < 0.0) {
        Controller->SetControlRotation(FRotator(0, 180, 0));
    }
    else {
        Controller->SetControlRotation(FRotator(0, 0, 0));
    }
}

void APlayerBase::MoveUp(float ScaleValue)
{
    AddMovementInput(FVector(0, 0, 1), ScaleValue, false);
}

void APlayerBase::UpdateFlipbook()
{
    auto FlipbookComponent = GetSprite();
    auto velocity = GetVelocity();
    if (velocity.Size() > 0) {
        FlipbookComponent->SetFlipbook(FlipbookLibrary[FString("Run")]);
        if (velocity.X < 0) {
            Controller->SetControlRotation(FRotator(0, 180, 0));
        }
        if (velocity.X > 0) {
            Controller->SetControlRotation(FRotator(0, 0, 0));
        }
    }
    else {
        FlipbookComponent->SetFlipbook(FlipbookLibrary[FString("Idle")]);
    }
}
