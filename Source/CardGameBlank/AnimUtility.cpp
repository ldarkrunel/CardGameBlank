// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimUtility.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieScene.h"
#include "Editor/MovieSceneTools/Public/KeyframeTrackEditor.h"
#include "Sections/MovieSceneFloatSection.h"
#include "Tracks/MovieScene3DTransformTrack.h"
#include "Tracks/MovieSceneFloatTrack.h"
#include "Card.h"
#include "CardGameInstance.h"

// Sets default values for this component's properties
UAnimUtility::UAnimUtility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UAnimUtility::BeginPlay()
{
	Super::BeginPlay();
}

void UAnimUtility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UAnimUtility* UCardGameInstance::AnimUtility()
{
	return IsValid(AnimUtilityInstance) ? AnimUtilityInstance : AnimUtilityInstance = NewObject<UAnimUtility>(this, FName("AnimUtility"));
}

ULevelSequence* UAnimUtility::GetAvaliableDrawCardAnim(ACard* Card)
{
	if (!DrawAnimPool.IsEmpty()) {
		ULevelSequence* LevelSequence;

		DrawAnimPool.Dequeue(LevelSequence);
		PoolSize--;
		return LevelSequence;
	}

	ULevelSequence* LevelSequenceCopy = DuplicateObject(DrawAnim, Card);
	PoolSize++;
	//reset level sequence anim back to default/start before returning it

	return LevelSequenceCopy;
}

void UAnimUtility::ReturnDrawCardAnimToPool(ULevelSequence* AnimToReturn)
{

	//set anim to start/default before making inactive
	//set to inactive

	DrawAnimPool.Enqueue(AnimToReturn);

}


void UAnimUtility::InitialisePool(ULevelSequence* AnimToDuplicate)
{
	DrawAnim = AnimToDuplicate;
	PoolInitialised = true;
}

bool UAnimUtility::UpdateLevelSequenceFloatKeyValue(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext, int ChannelNum, int FrameNum, float ModifiedValue)
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

void UAnimUtility::DisplayLevelSequenceKeyChannels(ULevelSequence* LevelSequence, UObject* Object, UWorld* WorldContext)
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

bool UAnimUtility::FindBinding(ULevelSequence* LevelSequence, UObject* Object, FGuid& Guid, UWorld* WorldContext)
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

void UAnimUtility::CleanUp()
{
	DrawAnim = nullptr;
	DrawAnimPool.Empty();
}

