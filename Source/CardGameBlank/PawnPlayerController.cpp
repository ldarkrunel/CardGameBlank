// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPlayerController.h"

APawnPlayerController::APawnPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
