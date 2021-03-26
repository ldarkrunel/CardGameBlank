// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck.h"
#include "InputCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "ECardState.h"
#include "Card.h"

// Sets default values
ADeck::ADeck()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void ADeck::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADeck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ACard* ADeck::SpawnNewCard()
{
	if (CardClass) {
		SpawnedCard = GetWorld()->SpawnActor<ACard>(CardClass, GetTransform().GetLocation(), GetTransform().GetRotation().Rotator());
		SpawnedCard->State = ECardState::ANIMATING;
		return SpawnedCard;
	}
	return nullptr;
}

void ADeck::DrawCard()
{
	if (CardsToDraw.Num() > 0) {
		CardsToDraw[0]->PlayDrawCardAnimation();
		CardsToDraw.RemoveAt(0);
		return;
	}

	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ADeck::DrawEachCardAfterDelay(TArray<ACard*>& Cards, float DelayBetweenDraws)
{
	CardsToDraw = Cards;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADeck::DrawCard, DelayBetweenDraws, true, 0.f);
}



