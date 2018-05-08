// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTS_UI.h"
#include "MyCameraPawn.h"
#include "Interfaces/Resource.h"
#include "GameFramework/GameModeBase.h"
#include "MyProject2GameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class MYPROJECT2_API AMyProject2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	AMyProject2GameModeBase();

	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class URTS_UI> rtsHUD_BP;
	UPROPERTY()
		class URTS_UI* currentWidget;

	UPROPERTY()
		class UUserWidget* iconBox;

public:
	URTS_UI* getUI() { return currentWidget; };

};


