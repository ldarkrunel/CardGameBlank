// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHand.h"
#include "Camera/CameraComponent.h"
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

	TArray<FVector> HandPositions = GetUpdatedCardPositionsInHand(GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation());

	for (auto position : HandPositions) {
		UE_LOG(LogTemp, Warning,TEXT("y position: %f"), position.Y);
	}
}


// Called every frame
void UPlayerHand::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

TArray<FVector> UPlayerHand::GetUpdatedCardPositionsInHand(FVector CenterHandPoint)
{
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
			FVector CardPosition = FVector{ CenterHandPoint.X,StartPoint + (i * localDistanceBetweenCards),CenterHandPoint.Z };
			CardPositionsInHand.Add(CardPosition);
		}
	}
	return CardPositionsInHand;
}

void UPlayerHand::UpdateCardPositions()
{

}

void UPlayerHand::AddCardToHand(ACard* CardToAdd)
{
	CardsInHand.Add(CardToAdd);

	//TArray<FVector> HandPositions = GetUpdatedCardPositionsInHand(GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation());

	//UpdateCardPositions
}

/*
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
*/

