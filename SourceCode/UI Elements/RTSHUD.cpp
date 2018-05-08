// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject2.h"
#include "RTSHUD.h"

/** boxHitActior
*
*@requires: drawBox() was previously called
*@returns:	actors with drawn box
*/
TArray<ACharacter*> ARTSHUD::boxHitActors() {
	
	return hitBots;
}

// Turn on/off box drawing
void ARTSHUD::setDrawBox(bool should) {
	
	bdrawBox = should;
	if (should) {
		hitBots.Empty();
		GetWorld()->GetFirstPlayerController()->GetMousePosition(StartPos.X, StartPos.Y);
	}
	else {
		selectTimer = 0.1;	//preset to grab quickly the first time
	}
}

// Draw box, save actors in temp array on a timer
void ARTSHUD::drawBox() {
	
	//Set end Pos of box to current mouse location
	GetWorld()->GetFirstPlayerController()->GetMousePosition(EndPos.X, EndPos.Y);			

	// Add to collection timer
	float dts = GetWorld()->GetDeltaSeconds();
	selectTimer += 1 * dts;

	// Only collect every 0.2 sec
	if (selectTimer >= 0.2) {
		hitBots.Empty();
		selectTimer = 0;
		GetActorsInSelectionRectangle(StartPos, EndPos, hitBots, false, false);
	}

	static FLinearColor sC = FLinearColor(0, 0.25, 0.25, 0.45);								//colour of box
	DrawRect(sC, StartPos.X, StartPos.Y, (EndPos.X - StartPos.X), (EndPos.Y - StartPos.Y));	//Draw box at start click, to curent pos
	
}

// constant tick
void ARTSHUD::DrawHUD()
{

	Super::DrawHUD();
	
	//if drawing box, draw
	if(bdrawBox){
		drawBox();
	}

}