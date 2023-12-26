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

    Health = MaxHealth;
    Mana = MaxMana;

    Controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);

    Controller->SetShowMouseCursor(true);

    MyMagicCircle = CreateWidget<UUserWidget>(Controller, MagicCircleClass);
    if (MyMagicCircle) MyMagicCircle->AddToViewport();                      //魔法阵Widget的显示AddToViewport

    // MyHealthbar= CreateWidget<UUserWidget>(Controller, HealthBarClass);  //血条Widget的显示AddToViewport
    // if (MyHealthbar) MyHealthbar->AddToViewport();
    //
    // MyManabar = CreateWidget<UUserWidget>(Controller, ManaBarClass);  //蓝条Widget的显示AddToViewport
    // if (MyManabar) MyManabar->AddToViewport();

    MyMainUI = CreateWidget<UUserWidget>(Controller, MainUIClass);
    if (MyMainUI) MyMainUI->AddToViewport();

    auto tempCircle = Cast<UMagicCircle>(MyMagicCircle);
    Translator->SetButtonNum(tempCircle->ButtonMap.Num());
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)  //设置玩家输入
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(InputComponent);

    InputComponent->BindAxis(TEXT("Move_Right"), this, &APlayerBase::MoveRight);
    InputComponent->BindAxis(TEXT("Move_Up"), this, &APlayerBase::MoveUp);
}

float APlayerBase::GetHealth()
{
    return Health;
}

float APlayerBase::GetMaxHealth()
{
    return MaxHealth;
}

float APlayerBase::GetMana()
{
    return Mana;
}

float APlayerBase::GetMaxMana()
{
    return MaxMana;
}

void APlayerBase::LoseMana(float amount) {
    Mana -= amount;
    if (Mana < 0) Mana = 0;
}

void APlayerBase::RestoreMana(float amount) {
    Mana += amount;
    if (Mana > MaxMana) Mana = MaxMana;
}

void APlayerBase::RestoreHealth(float amount)
{
    Health += amount;
    if (Health > MaxHealth) Health = MaxHealth;
}

int32 APlayerBase::GetCoin()
{
    return Coin;
}

void APlayerBase::AddCoin(int32 num)
{
    Coin += num;
}

bool APlayerBase::RemoveCoin(int32 num)
{
    if (Coin >= num) {
        Coin -= num;
        return true;
    }
    return false;
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

void APlayerBase::MoveRight(float ScaleValue)       //负数表示向左移动
{
    AddMovementInput(FVector(1, 0, 0), ScaleValue, false);
    if (ScaleValue < 0.0) {
        Controller->SetControlRotation(FRotator(0, 180, 0));
    }
    else {
        Controller->SetControlRotation(FRotator(0, 0, 0));
    }
}

void APlayerBase::MoveUp(float ScaleValue)      //负数代表向下移动
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

float APlayerBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float RealDamageAmout = DamageAmount * (1.0 - Defense);//玩家所受到的真实伤害
    Health -= RealDamageAmout;
    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);//报告所受到的伤害
    if (Health <= 0 && !IsDead)
    {
        Health = 0;
        Die();
    }
    return 0.0f;
}

void APlayerBase::Die()
{
    IsDead = true;
    if (!IsHadReportedDead)
    {
        IsHadReportedDead = true;
        UE_LOG(LogTemp, Warning, TEXT("You died!See you again!"));
    }

}