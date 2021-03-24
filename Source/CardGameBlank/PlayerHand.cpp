// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHand.h"
#include "Camera/CameraComponent.h"
#include "ECardState.h"
#include "AnimationComponent.h"
#include "TimerManager.h"
#include "Card.h"


// Sets default values for this component's properties
UPlayerHand::UPlayerHand()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UPlayerHand::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UPlayerHand::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

TArray<FVector> UPlayerHand::GetUpdatedCardPositionsInHand(FVector CenterHandPoint)
{
	//calculates the ideal locations for num cards in hand and returns them in an array

	TArray<FVector> CardPositionsInHand;
	if (CardClass) {
		float StartPoint = CenterHandPoint.Y;
		float localDistanceBetweenCards = MaxDistanceFromOtherCards;

		if (CardsInHand.Num() * MaxDistanceFromOtherCards > (MaxSpawnDistanceFromCentre * 2)) {
			StartPoint -= MaxSpawnDistanceFromCentre;
			localDistanceBetweenCards = (MaxSpawnDistanceFromCentre * 2) / (CardsInHand.Num() - 1);
		}
		else {
			if (CardsInHand.Num() % 2 == 0) {
				StartPoint -= (((CardsInHand.Num() - 2) / 2) * MaxDistanceFromOtherCards) + (MaxDistanceFromOtherCards / 2);
			}
			else {
				StartPoint -= (floor(CardsInHand.Num() / 2)) * MaxDistanceFromOtherCards;
			}
		}

		for (int i = 0; i < CardsInHand.Num(); i++)
		{
			FVector CardPosition = FVector{ CenterHandPoint.X - (i * DepthDifference),StartPoint + (i * localDistanceBetweenCards),CenterHandPoint.Z };
			CardPositionsInHand.Add(CardPosition);
		}
	}
	return CardPositionsInHand;
}

void UPlayerHand::UpdateCardPositions(TArray<FVector> DestinationCardPositions)
{
	for (int i = 0; i < CardsInHand.Num(); i++) {
		if (CardsInHand[i]->State == ECardState::IDLE) {

			FVector CardLocation = CardsInHand[i]->GetTransform().GetLocation();

			CardsInHand[i]->AnimComponent->CreateAnimation(FVector{ DestinationCardPositions[i].X - (i * DepthDifference), DestinationCardPositions[i].Y,CardLocation.Z }, 0.5f);
			CardsToLerpToDest.Add(CardsInHand[i]);
		}
	}

	GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UPlayerHand::AnimateCard, 0.2f, true, 0.5f);
}

void UPlayerHand::AnimateCard()
{
	if (CardsToLerpToDest.Num() > 0) {
		CardsToLerpToDest[0]->AnimComponent->Start();
		CardsToLerpToDest.RemoveAt(0);
		return;
	}

	GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
}

void UPlayerHand::AddCardToHand(ACard* CardToAdd)
{
	CardsInHand.Add(CardToAdd);
}

