// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API ARTSHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Variables for box drawing location
	FVector2D StartPos = FVector2D(0, 0);
	FVector2D EndPos = FVector2D(0, 0);
	TArray<ACharacter*> hitBots;
	float selectTimer = 0.0;
	bool bdrawBox;
	
	//Temo array for actors within drawn box
	TArray<ACharacter*> boxHitActors();
	void setDrawBox(bool should);

private:
	void drawBox();
	
	/*primary draw call for the HUD*/
	virtual void DrawHUD() override;

};
