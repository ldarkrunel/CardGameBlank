// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck.h"
#include "InputCoreTypes.h"
#include "GameFramework/PlayerController.h"
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

	bool KeyPressed = GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::E);

	if (KeyPressed) {
		UE_LOG(LogTemp, Warning, TEXT("E key was just pressed"));
		SpawnNewCard();
	}

}

void ADeck::SpawnNewCard()
{
	if (CardClass) {
		SpawnedCard = GetWorld()->SpawnActor<ACard>(CardClass, GetTransform().GetLocation(), GetTransform().GetRotation().Rotator());
	}
}

