// Fill out your copyright notice in the Description page of Project Settings.


#include "HighlightBlock.h"

// Sets default values
AHighlightBlock::AHighlightBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

}

// Called when the game starts or when spawned
void AHighlightBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHighlightBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

