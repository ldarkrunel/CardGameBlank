// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimUtil.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieScene.h"
#include "Editor/MovieSceneTools/Public/KeyframeTrackEditor.h"
#include "Sections/MovieSceneFloatSection.h"
#include "Tracks/MovieScene3DTransformTrack.h"
#include "Tracks/MovieSceneFloatTrack.h"
#include "Card.h"

AnimUtil::AnimUtil()
{
}



ULevelSequence* AnimUtil::GetAvaliableDrawCardAnim(ACard* Card)
{
	if (!DrawAnimPool.IsEmpty()) {

		ULevelSequence* LevelSequence;

		//set animation to active
		
		DrawAnimPool.Dequeue(LevelSequence);
		return LevelSequence;
	}

	ULevelSequence* LevelSequenceCopy = DuplicateObject(DrawAnim, Card);
	//reset level sequence anim back to default/start before returning it
	return LevelSequenceCopy;
	//DrawAnimPool.Enqueue(LevelSequenceCopy);
}

void AnimUtil::ReturnDrawCardAnimToPool(ULevelSequence* AnimToReturn)
{

	//set anim to start/default before making inactive
	//set to inactive

	DrawAnimPool.Enqueue(AnimToReturn);

}


void AnimUtil::InitialisePool(ULevelSequence* AnimToDuplicate)
{
	DrawAnim = AnimToDuplicate;
	PoolInitialised = true;
}

bool AnimUtil::UpdateLevelSequenceFloatKeyValue(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext,int ChannelNum, int FrameNum, float ModifiedValue)
{
	if (LevelSequence && Object) {
		FGuid Guid;
		if (FindBinding(LevelSequence, Object, Guid, WorldContext)) {

			UMovieScene3DTransformTrack* MovieSceneTrack = LevelSequence->MovieScene->FindTrack<UMovieScene3DTransformTrack>(Guid);

			if (MovieSceneTrack) {
				TArray<UMovieSceneSection*> MovieSceneSections = MovieSceneTrack->GetAllSections();

				if (MovieSceneSections.Num()) {
					UMovieScene3DTransformSection* TransformSection = nullptr;
					TransformSection = CastChecked<UMovieScene3DTransformSection>(MovieSceneSections[0]);

					if (TransformSection) {
						if (TransformSection->TryModify(true)) {
							TArrayView<FMovieSceneFloatChannel*> Channels = TransformSection->GetChannelProxy().GetChannels<FMovieSceneFloatChannel>();
							
							Channels[ChannelNum]->GetData().UpdateOrAddKey(FrameNum, FMovieSceneFloatValue(ModifiedValue));
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void AnimUtil::DisplayLevelSequenceKeyChannels(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext)
{
	if (LevelSequence && Object) {
		FGuid Guid;
		if (FindBinding(LevelSequence, Object, Guid, WorldContext)) {

			UMovieScene3DTransformTrack* MovieSceneTrack = LevelSequence->MovieScene->FindTrack<UMovieScene3DTransformTrack>(Guid);
			if (MovieSceneTrack) {
				TArray<UMovieSceneSection*> MovieSceneSections = MovieSceneTrack->GetAllSections();

				if (MovieSceneSections.Num()) {
					UMovieScene3DTransformSection* TransformSection = nullptr;
					TransformSection = CastChecked<UMovieScene3DTransformSection>(MovieSceneSections[0]);
					if (TransformSection) {
						if (TransformSection->TryModify(true)) {
							TArrayView<FMovieSceneFloatChannel*> Channels = TransformSection->GetChannelProxy().GetChannels<FMovieSceneFloatChannel>();

							for (int i = 0; i < Channels.Num(); i++) {

								UE_LOG(LogTemp, Warning, TEXT("channel: %i"), i);

								TMovieSceneChannelData<FMovieSceneFloatValue> data = Channels[i]->GetData();

								TArrayView<FFrameNumber> times = data.GetTimes();
								TArrayView<FMovieSceneFloatValue> values = data.GetValues();

								for (int j = 0; j < times.Num(); j++) {
									UE_LOG(LogTemp, Warning, TEXT("Frame Num: %i, Value: %f"), times[j].Value, values[j].Value);
								}

								UE_LOG(LogTemp, Warning, TEXT("................................"));
							}
						}
					}
				}
			}
		}
	}
}

bool AnimUtil::FindBinding(ULevelSequence* LevelSequence, UObject* Object, FGuid& Guid, UWorld* WorldContext)
{
	if (LevelSequence && Object)
	{

		for (auto b : LevelSequence->MovieScene->GetBindings())
		{

			FGuid ObjectGuid = b.GetObjectGuid();
			if (ObjectGuid.IsValid())
			{
				TArray<UObject*, TInlineAllocator<1>> Objects;
				LevelSequence->LocateBoundObjects(ObjectGuid, WorldContext, Objects);
				if (Objects.Num())
				{
					ACard* cardA = Cast<ACard>(Object);
					ACard* CardB = Cast<ACard>(Objects[0]);

					//UE_LOG(LogTemp, Warning, TEXT("Card A Name: %s"), *cardA->GetName());
					//UE_LOG(LogTemp, Warning, TEXT("Card B Name: %s"), *CardB->GetName());

					Guid = ObjectGuid;
					return true;

					if (Object == Objects[0])
					{
						UE_LOG(LogTemp, Warning, TEXT("44"));
						Guid = ObjectGuid;
						return true;
					}
				}
			}
		}
	}
	return false;
}

