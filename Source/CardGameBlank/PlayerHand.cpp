// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHand.h"
#include "Card.h"


// Sets default values for this component's properties
UPlayerHand::UPlayerHand()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


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

TArray<FVector> UPlayerHand::GetUpdatedCardPositionsInHand(FVector CenterHandPoint, int CurrentHandSize)
{
	TArray<FVector> CardPositionsInHand;

	if (CardClass) {
		float StartPoint = CenterHandPoint.Y;
		float localDistanceBetweenCards = MaxDistanceFromOtherCards;

		if (CurrentHandSize * MaxDistanceFromOtherCards > (MaxSpawnDistanceFromCentre * 2)) {
			StartPoint -= MaxSpawnDistanceFromCentre;
			localDistanceBetweenCards = (MaxSpawnDistanceFromCentre * 2) / (CurrentHandSize - 1);
		}
		else {
			if (CurrentHandSize % 2 == 0) {
				StartPoint -= (((CurrentHandSize - 2) / 2) * MaxDistanceFromOtherCards) + (MaxDistanceFromOtherCards / 2);
			}
			else {
				StartPoint -= (floor(CurrentHandSize / 2)) * MaxDistanceFromOtherCards;
			}
		}

		for (int i = 0; i < CurrentHandSize; i++)
		{
			FVector CardPosition = FVector{ CenterHandPoint.X,StartPoint + (i * localDistanceBetweenCards),CenterHandPoint.Z };
			CardPositionsInHand.Add(CardPosition);
		}
	}
	return CardPositionsInHand;
}

void UPlayerHand::UpdateCardPositions()
{

}

void UPlayerHand::PickUpCard(int NumCardsToPickup)
{

}


void UPlayerHand::SpawnHand(FVector SpawnPosition, FRotator CameraRot) {
	if (CardClass) {

		float StartPoint = SpawnPosition.Y;
		float localDistanceBetweenCards = MaxDistanceFromOtherCards;

		if (HandSize * MaxDistanceFromOtherCards > (MaxSpawnDistanceFromCentre * 2)) {
			StartPoint -= MaxSpawnDistanceFromCentre;
			localDistanceBetweenCards = (MaxSpawnDistanceFromCentre * 2) / (HandSize - 1);
		}
		else {
			if (HandSize % 2 == 0) {
				StartPoint -= (((HandSize - 2) / 2) * MaxDistanceFromOtherCards) + (MaxDistanceFromOtherCards / 2);
			}
			else {
				StartPoint -= (floor(HandSize / 2)) * MaxDistanceFromOtherCards;
			}
		}

		for (int i = 0; i < HandSize; i++)
		{
			ACard* Card = GetWorld()->SpawnActor<ACard>(CardClass, FVector{ SpawnPosition.X - (i * DepthDifference),StartPoint + (i * localDistanceBetweenCards),SpawnPosition.Z}, CameraRot);
			Cards.Add(Card);
		}
	}
}

