// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ULevelSequence;
class ACard;

static class CARDGAMEBLANK_API AnimUtil
{
public:
	AnimUtil();

	//static bool PoolInitialised;

	static bool FindBinding(ULevelSequence* LevelSequence, UObject* Object, FGuid& Guid, UWorld* WorldContext);
	static bool UpdateLevelSequenceFloatKeyValue(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext, int ChannelNum, int FrameNum, float ModifiedValue);
	static void DisplayLevelSequenceKeyChannels(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext);


	static ULevelSequence* GetAvaliableDrawCardAnim(ACard* Card);
	static void ReturnDrawCardAnimToPool(ULevelSequence* AnimToReturn);
	static void InitialisePool(ULevelSequence* AnimToDuplicate);

private:
	//static TQueue<ULevelSequence*> DrawAnimPool;
	//static ULevelSequence* DrawAnim;

};
