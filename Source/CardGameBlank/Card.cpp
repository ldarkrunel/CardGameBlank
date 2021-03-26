// Fill out your copyright notice in the Description page of Project Settings.

#include "Card.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "CardGameInstance.h"
#include "AnimUtility.h"
#include "Kismet/GameplayStatics.h"
#include "ECardState.h"
#include "IInteractable.h"
#include "AnimationComponent.h"

ACard::ACard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	CardBackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back Detail Mesh"));
	CardBackMesh->SetupAttachment(BaseMesh);

	CardFrontMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Detail Mesh"));
	CardFrontMesh->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();

	Initialize();

	if (SequencePlayer) 
		SequencePlayer->OnFinished.AddDynamic(this, &ACard::OnCardDrawn);

	AnimComponent = FindComponentByClass<UAnimationComponent>();

	//UClass* test = UInteractable::StaticClass();
}

void ACard::Initialize()
{
	UCardGameInstance* test = Cast<UCardGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!test->AnimUtility()->PoolInitialised)
		test->AnimUtility()->InitialisePool(DrawCard_Anim);

	//Creates the sequence actor which will play the animation for the card.

	if (DrawCard_Anim && !SequencePlayer) {
	
		LevelSequence = test->AnimUtility()->GetAvaliableDrawCardAnim(this);
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), OUT SequenceActor);
	}

	//Binds this card object to the sequence actor 

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

void ACard::HighlightActor(bool bIsHighlighted)
{

}

void ACard::OnCardDrawn()
{
	State = ECardState::IDLE;

	UCardGameInstance* test = Cast<UCardGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (test)
	{
		//return the draw animation to a pool to be re-used by other cards
		test->AnimUtility()->ReturnDrawCardAnimToPool(LevelSequence);
		test->AnimUtility()->PoolSize++;
	}
	

	if (SequenceActor) {
		//destroy the actor that is created in the level that plays the card animation
		SequenceActor->Destroy();
		SequenceActor = nullptr;
	}
}

void ACard::PlayDrawCardAnimation()
{
	SequencePlayer->Play();
}


//this could be moved to the animationcomponent inside card
void ACard::UpdateDrawCardAnimationEndLocation(int Channel, int FrameNum, float ModifiedValue)
{
	UCardGameInstance* test = Cast<UCardGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//updates card animation end key location so that each card goes to the desired point in player viewpoint

	if (test)
	{
		//test->AnimUtility()->UpdateLevelSequenceFloatKeyValue(LevelSequence, this, GetWorld(), Channel, FrameNum, ModifiedValue);
		test->AnimUtility()->DisplayLevelSequenceKeyChannels(LevelSequence, this, GetWorld());
	}
}

void ACard::UpdateDrawCardAnimationEndLocation(TArray<FLevelSequenceFloatData> LevelSequenceData)
{
	UCardGameInstance* test = Cast<UCardGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//updates card animation end key location so that each card goes to the desired point in player viewpoint

	if (test)
	{
		test->AnimUtility()->UpdateLevelSequenceFloatKeyValues(LevelSequence, this, GetWorld(), LevelSequenceData);
		//test->AnimUtility()->DisplayLevelSequenceKeyChannels(LevelSequence, this, GetWorld());
	}
}

void ACard::OnHoverStart()
{
	FVector MovedVector = { 20.0f,0,20.0f };

	if (State == ECardState::IDLE)
		AnimComponent->CreateAnimation(this->GetActorLocation() + MovedVector, 3.0f);

	AnimComponent->Start();
	//this->AddActorLocalOffset(this->GetActorLocation() + MovedVector, false, nullptr, ETeleportType::None);


	//AnimComponent->CreateAnimation(this->Transform)
	UE_LOG(LogTemp, Warning, TEXT("Card hover has just Started"));
}

void ACard::OnHoverEnd()
{
	AnimComponent->Reverse();
	UE_LOG(LogTemp, Warning, TEXT("Card hover has just ended"));
}

void ACard::OnSelectStart()
{

}

void ACard::OnSelectEnd()
{

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
