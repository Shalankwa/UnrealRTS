// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "RTSHUD.h"
#include "RTSController.h"
#include "MyProject2GameModeBase.h"
#include "Blueprint/UserWidget.h"


void AMyProject2GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AMyCameraPawn* myPawn = Cast<AMyCameraPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Connect UI to game
	if (rtsHUD_BP != nullptr) {
		currentWidget = CreateWidget<URTS_UI>(GetWorld(), rtsHUD_BP);

		if (currentWidget != nullptr) {
			Cast<UUserWidget>(currentWidget)->AddToViewport();	
		}
	}
}

AMyProject2GameModeBase::AMyProject2GameModeBase()
{
	//Set pawn, controller and HUD
	DefaultPawnClass = AMyCameraPawn::StaticClass();
	PlayerControllerClass = ARTSController::StaticClass();
	HUDClass = ARTSHUD::StaticClass();
}
