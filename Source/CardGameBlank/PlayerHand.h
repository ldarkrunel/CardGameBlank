// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHand.generated.h"

class ACard;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDGAMEBLANK_API UPlayerHand : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHand();

	void SpawnHand(FVector SpawnLocation, FRotator CameraRot);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACard> CardClass;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Hand", meta = (AllowPrivateAccess = "true"))
	TArray<ACard*> Cards;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand", meta = (AllowPrivateAccess = "true"))
	int HandSize = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HandSpawn", meta = (AllowPrivateAccess = "true"))
	float MaxSpawnDistanceFromCentre = 12.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HandSpawn", meta = (AllowPrivateAccess = "true"))
	float MaxDistanceFromOtherCards = 4.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HandSpawn", meta = (AllowPrivateAccess = "true"))
	float DepthDifference = 0.04f;

	TArray<FVector> GetUpdatedCardPositionsInHand(FVector HandCentrePoint, int CurrentHandSize);

	void UpdateCardPositions();

	void PickUpCard(int NumCardsToPickup);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
