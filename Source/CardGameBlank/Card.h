// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

class ULevelSequence;
class ULevelSequencePlayer;

UCLASS()
class CARDGAMEBLANK_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACard();

	FVector GetSize();

	void PlayDrawCardAnimation();

	void UpdateDrawCardAnimationEndLocation(int Channel, int FrameNum, float ModifiedValue);


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	ULevelSequence* DrawCard_Anim;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	ULevelSequencePlayer* SequencePlayer;

	UFUNCTION()
	void OnCardDrawn();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
