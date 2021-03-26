// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AnimUtility.generated.h"

class ULevelSequence;
class ACard;

struct FLevelSequenceFloatData
{
	int Channel;
	int FrameNum;
	float ModifiedValue;
};

UENUM()
enum class ELevelSequenceEditType : uint8
{
	LOCATION,
	ROTATION,
	SCALE
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CARDGAMEBLANK_API UAnimUtility : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAnimUtility();

	TQueue<ULevelSequence*> DrawAnimPool;
	ULevelSequence* DrawAnim;
	bool PoolInitialised = false;

	int PoolSize = 0;

	bool FindBinding(ULevelSequence* LevelSequence, UObject* Object, FGuid& Guid, UWorld* WorldContext);
	bool UpdateLevelSequenceFloatKeyValues(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext, TArray<FLevelSequenceFloatData> LevelSequenceFloatData);
	bool UpdateSingleLevelSequenceFloatKeyValue(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext, int Channel, int FrameNum, float ModifiedValue);
	void DisplayLevelSequenceKeyChannels(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext);

	ULevelSequence* GetAvaliableDrawCardAnim(ACard* Card);
	void ReturnDrawCardAnimToPool(ULevelSequence* AnimToReturn);
	void InitialisePool(ULevelSequence* AnimToDuplicate);

	TArray<FLevelSequenceFloatData> GetLevelSequenceEditData(ELevelSequenceEditType type, int FrameNum, FVector ModifiedValue);

	void CleanUp();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
