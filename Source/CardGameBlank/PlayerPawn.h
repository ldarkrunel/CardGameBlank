// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Deck.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class UInputComponent;
class UInteract;
class UPlayerHand;
class ULevelSequence;

UCLASS()
class CARDGAMEBLANK_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnClicked();

	void DrawCard(int NumCardsToDraw);


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* PlayerHandCentreLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* PlayerCardSpawnLocation;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInteract* PlayerInteractComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADeck> DeckClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	ULevelSequence* DrawAnim;

	ADeck* PlayerDeck;
	UPlayerHand* PlayerHand;

	void UpdatePlayerDrawCardAnimLocations();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
