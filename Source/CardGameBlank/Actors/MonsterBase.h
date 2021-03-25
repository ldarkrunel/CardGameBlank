// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardGameBlank/IInteractable.h"
#include "MonsterBase.generated.h"

UCLASS()
class CARDGAMEBLANK_API AMonsterBase : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	void HighlightActor(bool bIsHighlighted);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	AMonsterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnHoverStart() override;
	virtual void OnHoverEnd() override;

	virtual void OnSelectStart() override;
	virtual void OnSelectEnd() override;

};
