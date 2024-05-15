// Fill out your copyright notice in the Description page of Project Settings.


#include "GunsBoi.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "IceAndMetalGameModeBase.h"

// Sets default values
AGunsBoi::AGunsBoi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGunsBoi::BeginPlay()
{
	Super::BeginPlay();

    Health = MaxHealth;

	// Add Input Mapping Context
    PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
	{
        if(UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            InputSystem->AddMappingContext(GunsBoiMappingContext, 0);
        }
	}

    Gun = GetWorld()->SpawnActor<AGun>(GunClass);
    GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
    Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
    Gun->SetOwner(this);
}

// Called every frame
void AGunsBoi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunsBoi::Move(const FInputActionValue& Value)
{
    const FVector2D MoveVector = Value.Get<FVector2D>();

    if (Controller && (!MoveVector.IsNearlyZero()))
    {
        FVector XRight = GetActorRightVector();
        FVector YForward = GetActorForwardVector();

        AddMovementInput(XRight, MoveVector.X * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed);
        AddMovementInput(YForward, MoveVector.Y * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed);
    }
}

void AGunsBoi::Fire(const FInputActionValue& Value)
{
    Shoot();
}

void AGunsBoi::Shoot()
{
    Gun->PullTrigger();
}

void AGunsBoi::Look(const FInputActionValue& Value)
{
    const FVector2D LookXY = Value.Get<FVector2D>();

    if (Controller && (!LookXY.IsNearlyZero()))
    {
        FVector XRight = GetActorRightVector();
        FVector YForward = GetActorForwardVector();

        AddControllerPitchInput(LookXY.Y * UGameplayStatics::GetWorldDeltaSeconds(this) * LookSensitivityY);
        AddControllerYawInput(LookXY.X * UGameplayStatics::GetWorldDeltaSeconds(this) * LookSensitivityX);
    }
}

void AGunsBoi::Jump(const FInputActionValue& Value)
{
    ACharacter::Jump();
}

bool AGunsBoi::IsDead() const
{
    return Health <= 0;
}

float AGunsBoi::GetHealthPercentage() const
{
    return Health / MaxHealth;
}

// Called to bind functionality to input
void AGunsBoi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGunsBoi::Move);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AGunsBoi::Fire);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGunsBoi::Look);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AGunsBoi::Jump);
    }

}

float AGunsBoi::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    DamageToApply = FMath::Min(Health, DamageToApply);
    Health -= DamageToApply;

    if(IsDead())
    {
        AIceAndMetalGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AIceAndMetalGameModeBase>();
        if (GameMode != nullptr)
        {
            GameMode->PawnKilled(this);
        }

        DetachFromControllerPendingDestroy();
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    return DamageToApply;
}

