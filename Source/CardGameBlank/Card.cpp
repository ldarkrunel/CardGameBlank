// Fill out your copyright notice in the Description page of Project Settings.

#include "Card.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "AnimUtil.h"

ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();



	//UpdateDrawCardAnimationEndLocation(0, 0, 0.f);

	//SequencePlayer->OnFinished.AddDynamic(this, &ACard::OnCardDrawn);

}

void ACard::InitialiseAnim(int index) 
{
	ALevelSequenceActor* SequenceActor = nullptr;

	LevelSequence = DuplicateObject(DrawCard_Anim,this);

	//if (!AnimUtil::PoolInitialised) 
	//	AnimUtil::InitialisePool(DrawCard_Anim);

	if (DrawCard_Anim && !SequencePlayer) {
		if (index == 0)
			CurrentSequence = DrawCard_Anim;
		else
			CurrentSequence = LevelSequence;
	
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), CurrentSequence, FMovieSceneSequencePlaybackSettings(), OUT SequenceActor);
	}

	if (SequencePlayer) {

		CurrentSequence = SequenceActor->GetSequence();
		TArray<FMovieSceneBinding> Bindings = CurrentSequence->GetMovieScene()->GetBindings();

		TArray<UObject*, TInlineAllocator<1>> Objects;

		FMovieSceneObjectBindingID BindingId = FMovieSceneObjectBindingID(Bindings[0].GetObjectGuid(), MovieSceneSequenceID::Root);

		CurrentSequence->LocateBoundObjects(Bindings[0].GetObjectGuid(), GetWorld(), Objects);
		ACard* cardA = Cast<ACard>(Objects[0]);
		SequenceActor->AddBinding(BindingId, this);

		//SequenceActor->SetBinding(BindingId, TArray <AActor*> { this });
	}
}

void ACard::Initialize()
{
	//move this to header. sequence actor will need to be garbage collected after it has finished animation.
	ALevelSequenceActor* SequenceActor = nullptr;

	//if (!AnimUtil::PoolInitialised)
	//	AnimUtil::InitialisePool(DrawCard_Anim);

	if (DrawCard_Anim && !SequencePlayer) {

		LevelSequence = AnimUtil::GetAvaliableDrawCardAnim(this);

		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), OUT SequenceActor);
	}

	if (SequencePlayer) {

		LevelSequence = SequenceActor->GetSequence();
		TArray<FMovieSceneBinding> Bindings = LevelSequence->GetMovieScene()->GetBindings();

		TArray<UObject*, TInlineAllocator<1>> Objects;

		FMovieSceneObjectBindingID BindingId = FMovieSceneObjectBindingID(Bindings[0].GetObjectGuid(), MovieSceneSequenceID::Root);

		LevelSequence->LocateBoundObjects(Bindings[0].GetObjectGuid(), GetWorld(), Objects);
		ACard* cardA = Cast<ACard>(Objects[0]);
		SequenceActor->AddBinding(BindingId, this);
	}
}

void ACard::OnCardDrawn()
{
	//garbage collect sequence actor associated with this card
	//return level sequence to the pool

}

void ACard::PlayDrawCardAnimation()
{
	SequencePlayer->Play();

}

void ACard::UpdateDrawCardAnimationEndLocation(int Channel, int FrameNum, float ModifiedValue, int LoopIndex)
{
	for (int i = 0; i < 2; i++) {
		if (LoopIndex == 0) {
			UE_LOG(LogTemp, Warning, TEXT("gets here first"));
			AnimUtil::UpdateLevelSequenceFloatKeyValue(DrawCard_Anim, this, GetWorld(), Channel, FrameNum, ModifiedValue);
			AnimUtil::DisplayLevelSequenceKeyChannels(DrawCard_Anim, this, GetWorld());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("gets here second"));
			AnimUtil::UpdateLevelSequenceFloatKeyValue(LevelSequence, this, GetWorld(), Channel, FrameNum, ModifiedValue);
			AnimUtil::DisplayLevelSequenceKeyChannels(LevelSequence, this, GetWorld());
		}
		PlayDrawCardAnimation();
	}
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ACard::GetSize()
{
	FBox CardBoxBounds = BaseMesh->CalcLocalBounds().GetBox();
	
	return FVector{ CardBoxBounds.GetSize().X,CardBoxBounds.GetSize().Y,CardBoxBounds.GetSize().Z };
}

void ACard::ChangeName(FString Name)
{
	CardName = Name;
}

FString ACard::GetNewName()
{
	return CardName;
}
