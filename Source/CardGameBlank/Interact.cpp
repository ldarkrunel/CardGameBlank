// Fill out your copyright notice in the Description page of Project Settings.

#include "Interact.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "IInteractable.h"
#include "HighlightBlock.h"

// Sets default values for this component's properties
UInteract::UInteract()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInteract::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	if (BlockClass) {
		FVector SpawnLocation{ 0,0,0 };
		FRotator SpawnRotation{ 0,0,0 };

		Block = GetWorld()->SpawnActor<AHighlightBlock>(BlockClass, SpawnLocation, SpawnRotation);
	}
}


// Called every frame
void UInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PC) {
		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f); //change to a distance variable

		TraceForInteractable(Start, End, false);

		//TraceForBlock(Start, End, false);
	}

}

void UInteract::PerformRayCastFromMouse()
{
	FVector Start, Dir, End;
	PC->DeprojectMousePositionToWorld(Start, Dir);
	End = Start + (Dir * 8000.0f); //change to a distance variable

	SelectInteractable(Start, End, false);

	UE_LOG(LogTemp, Warning, TEXT("Performing raycast from mouse position"));
}

void UInteract::TraceForInteractable(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}

	if (!HitResult.Actor.IsValid()) {
		if (CurrentlyHighlightedInteractable != nullptr) {
			CurrentlyHighlightedInteractable->OnHoverEnd();
			CurrentlyHighlightedInteractable = nullptr;
		}
		return;
	}

	FVector_NetQuantize HitPoint = HitResult.ImpactPoint;

	IInteractable* CurrentInteractable = Cast<IInteractable>(HitResult.Actor);

	if (CurrentInteractable) {
		if (CurrentlyHighlightedInteractable == nullptr) {
			CurrentInteractable->OnHoverStart();
			CurrentlyHighlightedInteractable = CurrentInteractable;
		}
		else if (CurrentInteractable != CurrentlyHighlightedInteractable) {
			CurrentlyHighlightedInteractable->OnHoverEnd();
			CurrentlyHighlightedInteractable = CurrentInteractable;
			CurrentlyHighlightedInteractable->OnHoverStart();
		}
	}
}

void UInteract::SelectInteractable(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}

	if (!HitResult.Actor.IsValid()) {
		if (CurrentlySelectedInteractable != nullptr) {
			CurrentlySelectedInteractable->OnSelectEnd();
			CurrentlySelectedInteractable = nullptr;
		}
		return;
	}

	FVector_NetQuantize HitPoint = HitResult.ImpactPoint;

	IInteractable* CurrentInteractable = Cast<IInteractable>(HitResult.Actor);

	if (CurrentInteractable) {
		if (CurrentlySelectedInteractable == nullptr) {
			CurrentInteractable->OnSelectStart();
			CurrentlySelectedInteractable = CurrentInteractable;
		}
		else if (CurrentInteractable != CurrentlySelectedInteractable) {
			CurrentlySelectedInteractable->OnSelectEnd();
			CurrentlySelectedInteractable = CurrentInteractable;
			CurrentlySelectedInteractable->OnSelectStart();
		}
	}
}

/*
void UInteract::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}

	FVector_NetQuantize HitPoint = HitResult.ImpactPoint;

	if (HitResult.Actor.IsValid())
	{
		AActor* HitActor = HitResult.Actor.Get();

		if (HitActor != CurrentActor.currentActor) {
			CurrentActor.currentActor = HitActor;
			FBoxSphereBounds BoardBoxBounds = HitActor->FindComponentByClass<UStaticMeshComponent>()->Bounds;
			CurrentActor.Location = HitActor->GetActorLocation();
			CurrentActor.XPosition = BoardBoxBounds.GetBox().GetSize().X;
			CurrentActor.YPosition = BoardBoxBounds.GetBox().GetSize().Y;
		}

		float FlooredXPoint = floor(HitPoint.X / 100) * 100 + 50;
		float FlooredYPoint = floor(HitPoint.Y / 100) * 100 + 50;

		//UE_LOG(LogTemp, Warning, TEXT("nearest point: x: %f, y: %f"), FlooredXPoint, FlooredYPoint);

		if (Block) {
			Block->SetActorLocation(FVector{ FlooredXPoint,FlooredYPoint,43 });
		}
	}
}
*/


