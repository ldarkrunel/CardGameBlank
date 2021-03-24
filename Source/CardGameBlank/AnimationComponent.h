// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CARDGAMEBLANK_API UAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAnimationComponent();

	bool IsAnimating = false;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Location", meta = (AllowPrivateAccess = "true"))
		FVector StartLocation;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Location", meta = (AllowPrivateAccess = "true"))
		FVector DestLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		float AnimSpeed;

	float Alpha = 0.f;

	void CreateAnimation(FVector destination, float AnimSpeed);

	void CreateAnimation(FVector InitalPosition, FVector Destination, float AnimSpeed);

	void Start();


private:
	void AnimateComponent(float DeltaTime);
	float EaseInOut(float t);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
