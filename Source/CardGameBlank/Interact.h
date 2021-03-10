// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Card.h"
#include "Interact.generated.h"


class UInputComponent;
class AHighlightBlock;

struct FCurrentActorDetails
{
	AActor* currentActor;
	FVector Location;
	float XPosition;
	float YPosition;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDGAMEBLANK_API UInteract : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteract();
	void SetUpInputComponent(UInputComponent* PlayerInputComponent);

private:

	FCurrentActorDetails CurrentActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHighlightBlock> BlockClass;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Block", meta = (AllowPrivateAccess = "true"))
	AHighlightBlock* Block;

	void PerformRayCastFromMouse();
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
