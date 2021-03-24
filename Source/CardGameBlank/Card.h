// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ECardState.h"
#include "IInteractable.h"
#include "Card.generated.h"

class ULevelSequence;
class ULevelSequencePlayer;
class ALevelSequenceActor;
class UAnimationComponent;

UCLASS()
class CARDGAMEBLANK_API ACard : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACard();

	ECardState State;

	UAnimationComponent* AnimComponent;

	FVector GetSize();

	void PlayDrawCardAnimation();

	void UpdateDrawCardAnimationEndLocation(int Channel, int FrameNum, float ModifiedValue);

	virtual void OnHoverStart() override;
	virtual void OnHoverEnd() override;

	virtual void OnSelectStart() override;
	virtual void OnSelectEnd() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CardBackMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	ULevelSequence* DrawCard_Anim;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	ULevelSequence* LevelSequence;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	ALevelSequenceActor* SequenceActor = nullptr;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	ULevelSequencePlayer* SequencePlayer;

	UFUNCTION()
	void OnCardDrawn();

	void Initialize();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};



