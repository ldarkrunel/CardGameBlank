// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationComponent.h"

// Sets default values for this component's properties
UAnimationComponent::UAnimationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UAnimationComponent::CreateAnimation(FVector destination, float Speed)
{
	StartLocation = GetOwner()->GetTransform().GetLocation();
	DestLocation = destination;
	AnimSpeed = Speed;
	ReverseAnim = false;
}

void UAnimationComponent::CreateAnimation(FVector InitalPosition, FVector Destination, float Speed)
{
	StartLocation = InitalPosition;
	DestLocation = Destination;
	AnimSpeed = Speed;

}

void UAnimationComponent::Start()
{
	ReverseAnim = false;
	IsAnimating = true;
}

void UAnimationComponent::Reverse()
{
	ReverseAnim = true;
	IsAnimating = true;
}

void UAnimationComponent::AnimateComponent(float DeltaTime)
{
	FVector CurrentLocation;

	if (!ReverseAnim)
		Alpha += DeltaTime * AnimSpeed;
	else
		Alpha -= DeltaTime * AnimSpeed;

	if (Alpha > 1)
		Alpha = 1.0f;
	else if (Alpha < 0)
		Alpha = 0.f;

	CurrentLocation = FMath::Lerp(StartLocation, DestLocation, Alpha);

	GetOwner()->SetActorLocation(CurrentLocation);

	if (Alpha >= 1 || Alpha <= 0) {
		IsAnimating = false;
		if (ReverseAnim)
			Alpha = 0.f;
		else
			Alpha = 1.f;
	}
}

float UAnimationComponent::EaseInOut(float t)
{
	return t < .5f ? 4 * t * t * t : (t - 1) * (2 * t - 2) * (2 * t - 2) + 1;
}

// Called when the game starts
void UAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	TScriptDelegate<FWeakObjectPtr> AnimFinished;
}

// Called every frame
void UAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsAnimating)
		AnimateComponent(DeltaTime);
}

