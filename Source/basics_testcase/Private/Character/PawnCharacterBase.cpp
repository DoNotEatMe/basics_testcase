// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PawnCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Character/BasicMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/CharacterStatsComponent.h"
#include "GameFramework/BasicHUD.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APawnCharacterBase::APawnCharacterBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->InitCapsuleSize(34.f, 88.f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	Camera->bUsePawnControlRotation = false;

	MovementComponent = CreateDefaultSubobject<UBasicMovementComponent>(TEXT("MovementComponent"));
	StatsComponent = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("Stats"));
}

// Called when the game starts or when spawned
void APawnCharacterBase::BeginPlay()
{
	Super::BeginPlay();


	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (StatsComponent)
	{
		StatsComponent->InitializeStats();

		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (ABasicHUD* HUD = Cast<ABasicHUD>(PC->GetHUD()))
			{
				HUD->SpawnUI(StatsComponent);
			}
		}
	}
}

// Called every frame
void APawnCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(InputMove, ETriggerEvent::Triggered, this, &APawnCharacterBase::HandleMove);
		EnhancedInput->BindAction(InputLook, ETriggerEvent::Triggered, this, &APawnCharacterBase::HandleLook);
		EnhancedInput->BindAction(InputFire, ETriggerEvent::Started, this, &APawnCharacterBase::HandleFire);
		EnhancedInput->BindAction(InputHeal, ETriggerEvent::Started, this, &APawnCharacterBase::HandleHeal);
		EnhancedInput->BindAction(InputAddMP, ETriggerEvent::Started, this, &APawnCharacterBase::HandleAddMP);
	}
}

void APawnCharacterBase::HandleMove(const FInputActionValue& Value)
{
	MovementComponent->Move(Value.Get<FVector2D>(), GetWorld()->GetDeltaSeconds());
}

void APawnCharacterBase::HandleLook(const FInputActionValue& Value)
{
	MovementComponent->Look(Value.Get<FVector2D>(), GetWorld()->GetDeltaSeconds());
}

void APawnCharacterBase::HandleFire(const FInputActionValue& Value)
{
	if (!Camera) return;

	if (StatsComponent->CurrentMP < 3.f) return;

	FHitResult Hit;
	FVector CameraLocation = Camera->GetComponentLocation();
	FVector EndTrace = CameraLocation + Camera->GetForwardVector() * 5000.f;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	StatsComponent->UseMP(3.f);

	bool bHit = World->LineTraceSingleByChannel(Hit, CameraLocation, EndTrace, ECC_Visibility, Params);
	if (bHit)
	{

		
		if (AActor* Target = Hit.GetActor())
		{
			UGameplayStatics::ApplyDamage(
				Target,
				100.f,
				Controller,
				this,
				UDamageType::StaticClass()
			);
		}
		// DrawDebugLine(World, CameraLocation, EndTrace, FColor::Green, false, 5.f);
		// DrawDebugSphere(World, Hit.Location, 50.f, 20, FColor::Red, true, 5.f);
	}
}

inline void APawnCharacterBase::HandleHeal(const FInputActionValue& Value)
{
	StatsComponent->Heal(10.f);
}


void APawnCharacterBase::HandleAddMP(const FInputActionValue& Value)
{
	StatsComponent->RestoreMP(100.f);
}