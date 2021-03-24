// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//#include "Engine/ObjectLibrary.h"
#include "CardGameInstance.generated.h"

class UAnimUtility;
//class UObjectLibrary;
class UTexture2D;

UCLASS()
class CARDGAMEBLANK_API UCardGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintPure,
		Category = "Persistence",
		meta = (
			DisplayName = "Get Savegame Manager",
			Keywords = "SavegameManager"))
		UAnimUtility* AnimUtility();

protected:
	virtual void Shutdown() override;
	virtual void Init() override;


private:
	UPROPERTY(Transient)
	UAnimUtility* AnimUtilityInstance;

	//UObjectLibrary ObjectLibrary;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UTexture2D> Texture2DClass;

	void LoadCardTextures();

};
