// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Deck.h"
#include "Card.h"
#include "PlayerHand.h"
#include "Camera/CameraComponent.h"
//#include "CardGameInstance.h"
//#include "AnimUtility.h"
#include "Interact.h"
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
	PlayerInteractComponent = FindComponentByClass<UInteract>();

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

	if (KeyPressed)
		DrawCard(3);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerPawn::OnClicked);
}

void APlayerPawn::OnClicked()
{
	if (PlayerInteractComponent)
		PlayerInteractComponent->PerformRayCastFromMouse();
}

void APlayerPawn::DrawCard(int NumCardsToDraw)
{
	if (PlayerHand && PlayerDeck) {

		TArray<ACard*> CardsToDraw;

		for (int i = 0; i < NumCardsToDraw; i++) {
			ACard* SpawnedCard = PlayerDeck->SpawnNewCard();
			PlayerHand->AddCardToHand(SpawnedCard);
			CardsToDraw.Add(SpawnedCard);
		}

		TArray<FVector> UpdatedCardPositionsInHand = PlayerHand->GetUpdatedCardPositionsInHand(PlayerHandSpawnLocation->GetComponentTransform().GetLocation());

		for (int i = 0; i < CardsToDraw.Num(); i++) {
			CardsToDraw[i]->UpdateDrawCardAnimationEndLocation(1, 119484, UpdatedCardPositionsInHand[UpdatedCardPositionsInHand.Num() - CardsToDraw.Num() + i].Y);
		}

		PlayerDeck->DrawEachCardAfterDelay(CardsToDraw, 0.2f);
		PlayerHand->UpdateCardPositions(UpdatedCardPositionsInHand);
	}
}
