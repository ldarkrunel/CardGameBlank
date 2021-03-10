// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "PlayerHand.h"
#include "Camera/CameraComponent.h"

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

	FTransform test = PlayerHandSpawnLocation->GetComponentTransform();
	if (PlayerHand) {
		PlayerHand->SpawnHand(PlayerHandSpawnLocation->GetComponentTransform().GetLocation(), PlayerCamera->GetComponentRotation());
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
