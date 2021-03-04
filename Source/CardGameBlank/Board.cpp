// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Board = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = Board;

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

	GameBoard = GetOwner()->FindComponentByClass<UStaticMeshComponent>();

	FBoxSphereBounds BoardBoxBounds = GameBoard->Bounds;
	BoardX = BoardBoxBounds.GetBox().GetSize().X;
	BoardY = BoardBoxBounds.GetBox().GetSize().Y;
	
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

