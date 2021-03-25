// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "Components/CapsuleComponent.h"
#include "CardGameBlank/IInteractable.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterBase::OnHoverStart()
{
	HighlightActor(true);
}

void AMonsterBase::OnHoverEnd()
{
	HighlightActor(false);
}

void AMonsterBase::OnSelectStart()
{

}

void AMonsterBase::OnSelectEnd()
{

}

void AMonsterBase::HighlightActor(bool bIsHighlighted)
{
	BaseMesh->SetRenderCustomDepth(bIsHighlighted);
}