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

void AnimUtil::DisplayLevelSequenceKeyChannels(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext) 
{

	UE_LOG(LogTemp, Warning, TEXT("1"));
	if (LevelSequence && Object) {
		FGuid Guid;
		UE_LOG(LogTemp, Warning, TEXT("2"));
		if (FindBinding(LevelSequence, Object, Guid, WorldContext)) {

			UMovieScene3DTransformTrack* MovieSceneTrack = LevelSequence->MovieScene->FindTrack<UMovieScene3DTransformTrack>(Guid);
			UE_LOG(LogTemp, Warning, TEXT("3"));
			if (MovieSceneTrack) {
				TArray<UMovieSceneSection*> MovieSceneSections = MovieSceneTrack->GetAllSections();

				if (MovieSceneSections.Num()) {
					UMovieScene3DTransformSection* TransformSection = nullptr;
					TransformSection = CastChecked<UMovieScene3DTransformSection>(MovieSceneSections[0]);
					UE_LOG(LogTemp, Warning, TEXT("4"));
					if (TransformSection) {
						if (TransformSection->TryModify(true)) {
							TArrayView<FMovieSceneFloatChannel*> Channels = TransformSection->GetChannelProxy().GetChannels<FMovieSceneFloatChannel>();

							for (int i = 0; i < Channels.Num(); i++) {

								UE_LOG(LogTemp, Warning, TEXT("channel: %i"), i);

								TMovieSceneChannelData<FMovieSceneFloatValue> data = Channels[i]->GetData();

								for (auto value : data.GetValues()) {
									UE_LOG(LogTemp, Warning, TEXT("value: %f"), value.Value);
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

bool AnimUtil::FindBinding(ULevelSequence* LevelSequence, UObject* Object, FGuid& Guid, UWorld* WorldContext)
{
	if (LevelSequence && Object)
	{
		UE_LOG(LogTemp, Warning, TEXT("11"));
		for (auto b : LevelSequence->MovieScene->GetBindings())
		{
			FGuid ObjectGuid = b.GetObjectGuid();
			if (ObjectGuid.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("22"));
				TArray<UObject*, TInlineAllocator<1>> Objects;
				LevelSequence->LocateBoundObjects(ObjectGuid, WorldContext, Objects);
				if (Objects.Num())
				{
					UE_LOG(LogTemp, Warning, TEXT("33"));

					ACard* cardA = Cast<ACard>(Object);
					ACard* CardB = Cast<ACard>(Objects[0]);

					UE_LOG(LogTemp, Warning, TEXT("Card A Name: %s"), *cardA->GetName());
					UE_LOG(LogTemp, Warning, TEXT("Card B Name: %s"), *CardB->GetName());


					if (Object == Objects[0])
					{
						UE_LOG(LogTemp, Warning, TEXT("44"));
						UE_LOG(LogTemp, Warning, TEXT("getting here in static class?"));
						Guid = ObjectGuid;
						return true;
					}
				}
			}
		}
	}
	return false;
}

