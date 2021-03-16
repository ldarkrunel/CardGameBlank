// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Deck.h"
#include "Card.h"
#include "PlayerHand.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Base Mesh"));
	RootComponent = PlayerCamera;

	PlayerHandSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Player Hand"));
	PlayerHandSpawnLocation->SetupAttachment(PlayerCamera);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();


	PlayerHand = FindComponentByClass<UPlayerHand>();

	TArray<AActor*> decksFound;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DeckClass, decksFound);

	if (decksFound.Num() > 0) 
		PlayerDeck = Cast<ADeck>(decksFound[0]);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool KeyPressed = GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::E);

	if (KeyPressed) {
		//UE_LOG(LogTemp, Warning, TEXT("E key was just pressed"));
		DrawCard(1);
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerPawn::OnClicked);
}

void APlayerPawn::OnClicked() 
{
	UE_LOG(LogTemp, Warning, TEXT("can i see this text?"));
}

void APlayerPawn::DrawCard(int NumCardsToDraw)
{

	if (PlayerHand && PlayerDeck) {

		ACard* SpawnedCard = PlayerDeck->SpawnNewCard();
		SpawnedCard->UpdateDrawCardAnimationEndLocation(0, 0, 0.f);
		//SpawnedCard->Name
	}

	/*
	if (PlayerHand && PlayerDeck) {

		TArray<ACard*> CardsToDraw;

		for (int i = 0; i < NumCardsToDraw; i++) {
			ACard* SpawnedCard = PlayerDeck->SpawnNewCard();
			PlayerHand->AddCardToHand(SpawnedCard);
			CardsToDraw.Add(SpawnedCard);
		}

		TArray<FVector> UpdatedCardPositionsInHand = PlayerHand->GetUpdatedCardPositionsInHand(PlayerCamera->GetComponentTransform().GetLocation());

		CardsToDraw[0]->UpdateDrawCardAnimationEndLocation(2, 2, UpdatedCardPositionsInHand[UpdatedCardPositionsInHand.Num() - CardsToDraw.Num() + 0].Y);


		for (int i = 0; i < CardsToDraw.Num(); i++) {
			CardsToDraw[i]->UpdateDrawCardAnimationEndLocation(2, 2, UpdatedCardPositionsInHand[UpdatedCardPositionsInHand.Num() - CardsToDraw.Num() + i].Y);
		}

		PlayerDeck->DrawEachCardAfterDelay(CardsToDraw, 0.3f);

	}
		*/
}
