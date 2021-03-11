// Fill out your copyright notice in the Description page of Project Settings.

#include "Card.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieScene.h"


// Sets default values


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

	ALevelSequenceActor* SequenceActor = nullptr;

	if (DrawCard_Anim && !SequencePlayer)
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), DrawCard_Anim, FMovieSceneSequencePlaybackSettings(), OUT SequenceActor);

	if (SequencePlayer) {

		ULevelSequence* LevelSequence = SequenceActor->GetSequence();
		TArray<FMovieSceneBinding> Bindings = LevelSequence->GetMovieScene()->GetBindings();

		FMovieSceneObjectBindingID BindingId = FMovieSceneObjectBindingID(Bindings[0].GetObjectGuid(), MovieSceneSequenceID::Root);

		SequenceActor->SetBinding(BindingId, TArray <AActor*> { this });

		SequencePlayer->Play();

	}

	//SequencePlayer->OnFinished.AddDynamic(this, &ACard::OnCardDrawn);

}

void ACard::OnCardDrawn()
{
	//UE_LOG(LogTemp, Warning, TEXT("Card has finished being drawn"));
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//IMovieScenePlayer player;

	//DrawAnim->CreateDirectorInstance(player);

}

FVector ACard::GetSize()
{
	FBox CardBoxBounds = BaseMesh->CalcLocalBounds().GetBox();
	
	return FVector{ CardBoxBounds.GetSize().X,CardBoxBounds.GetSize().Y,CardBoxBounds.GetSize().Z };
}

