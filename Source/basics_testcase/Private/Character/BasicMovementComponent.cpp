// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BasicMovementComponent.h"

#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UBasicMovementComponent::UBasicMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBasicMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		Camera = OwnerPawn->FindComponentByClass<UCameraComponent>();
	}
}


void UBasicMovementComponent::Move(const FVector2D& Input, float DeltaTime)
{
	if (!OwnerPawn) return;

	const FVector Direction =
		OwnerPawn->GetActorForwardVector() * Input.X +
		OwnerPawn->GetActorRightVector() * Input.Y;

	OwnerPawn->AddActorWorldOffset(Direction * MoveSpeed * DeltaTime, true);
}

void UBasicMovementComponent::Look(const FVector2D& Input, float DeltaTime)
{
	if (!OwnerPawn || !Camera) return;
	
	FRotator ActorRot = OwnerPawn->GetActorRotation();
	ActorRot.Yaw += Input.X * LookSpeed * DeltaTime;
	OwnerPawn->SetActorRotation(ActorRot);

	FRotator CameraRot = Camera->GetRelativeRotation();
	CameraRot.Pitch = FMath::Clamp(CameraRot.Pitch + Input.Y * LookSpeed * DeltaTime, MinPitch, MaxPitch);
	Camera->SetRelativeRotation(CameraRot);
}