// Fill out your copyright notice in the Description page of Project Settings.

#include "Interact.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
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
	UE_LOG(LogTemp, Warning, TEXT("Interact initialized"));

	if (BlockClass) {
		FVector SpawnLocation{ 0,0,0 };
		FRotator SpawnRotation{ 0,0,0 };
		UE_LOG(LogTemp, Warning, TEXT("card initialized"));

		Block = GetWorld()->SpawnActor<AHighlightBlock>(BlockClass, SpawnLocation, SpawnRotation);
		//TempCard->SetOwner(this);
	}

}


// Called every frame
void UInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController())) {
		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f); //change to a distance variable
		TraceForBlock(Start, End, false);
	}

}

void UInteract::SetUpInputComponent(UInputComponent* PlayerInputComponent)
{
	if (PlayerInputComponent) {
		UE_LOG(LogTemp, Error, TEXT("Input component found on: %s"), *GetOwner()->GetName());
		PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &UInteract::PerformRayCastFromMouse);
	}
}

void UInteract::PerformRayCastFromMouse()
{
	UE_LOG(LogTemp, Warning, TEXT("clicking?"));
}

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

	//UE_LOG(LogTemp, Warning, TEXT("x pos: %f, y pos: %f"), HitPoint.X, HitPoint.Y);

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
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Hitting nothing"));
	}
}


