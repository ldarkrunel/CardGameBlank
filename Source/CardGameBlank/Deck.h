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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACard> CardClass;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Card", meta = (AllowPrivateAccess = "true"))
	ACard* SpawnedCard;

	void SpawnNewCard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
