// Fill out your copyright notice in the Description page of Project Settings.

#include "CardGameInstance.h"
#include "Engine/ObjectLibrary.h"
#include "AnimUtility.h"


void UCardGameInstance::Shutdown()
{
	Super::Shutdown();
	AnimUtility()->CleanUp();
}

void UCardGameInstance::Init()
{
	Super::Init();
}

void UCardGameInstance::LoadCardTextures()
{
	//FJsonSerializableArray()
	//FString Path = "D:/Unreal Engine/Projects/4.24/CardGameBlank/Content/Textures/Cards/en_3tc8CwgpKL.uasset";
	//UObjectLibrary::LoadAssetsFromPath(Path);

	//UObjectLibrary::CreateLibrary(UTexture2D,)
}
