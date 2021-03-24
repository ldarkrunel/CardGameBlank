// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MonsterBase.generated.h"

UCLASS()
class CARDGAMEBLANK_API AMonsterBase : public APawn
{
	GENERATED_BODY()

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	// Attributes
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	int32 MaxHealth = 0;
	UPROPERTY(VisibleAnywhere, Category = "Attributes")
	int32 CurrentHealth = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	int32 MovementSpeed = 0;

	void MoveToLocation(FVector Location);
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	AMonsterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
