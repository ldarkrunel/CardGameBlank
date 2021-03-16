// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Deck.generated.h"

class ACard;

UCLASS()
class CARDGAMEBLANK_API ADeck : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeck();

	virtual void Tick(float DeltaTime) override;

	ACard* SpawnNewCard();

	void DrawEachCardAfterDelay(TArray<ACard*> Cards, float DelayBetweenDraws);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACard> CardClass;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Card", meta = (AllowPrivateAccess = "true"))
	ACard* SpawnedCard;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Card", meta = (AllowPrivateAccess = "true"))
	int NumCardsLeftToDraw = 0;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	FTimerHandle TimerHandle;

	void DrawCard(TArray<ACard*> Cards);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
