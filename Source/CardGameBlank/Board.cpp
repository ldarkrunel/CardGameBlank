// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "IInteractable.h"
// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Board = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = Board;

}

void ABoard::OnSelectStart()
{

}

void ABoard::OnSelectEnd()
{

}

void ABoard::OnHoverStart()
{
	UE_LOG(LogTemp, Warning, TEXT("Board is being highlighted"));
}

void ABoard::OnHoverEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Board has stopped being highlighted"));
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

	//GameBoard = GetOwner()->FindComponentByClass<UStaticMeshComponent>();

	FBoxSphereBounds BoardBoxBounds = Board->Bounds;
	BoardX = BoardBoxBounds.GetBox().GetSize().X;
	BoardY = BoardBoxBounds.GetBox().GetSize().Y;

	UE_LOG(LogTemp, Warning, TEXT("Board x size: %f"), BoardX);
	UE_LOG(LogTemp, Warning, TEXT("Board y size: %f"), BoardY);
	//UE_LOG(LogTemp, Warning, TEXT("Is working"));
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

