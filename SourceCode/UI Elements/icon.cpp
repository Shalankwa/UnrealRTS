// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject2.h"
#include "icon.h"


void Uicon::SetIconTexture(UTexture2D * unit)
{
	iconTexture = unit;
}
void Uicon::Message()
{
	UE_LOG(LogTemp, Warning, TEXT("We call Onclick"));
}
void Uicon::setOnclick()
{
	iconButton = (UButton*)GetWidgetFromName(TEXT("iconButton"));
	//iconButton->OnClicked.AddDynamic(this, &Uicon::unSelect);
}

void Uicon::unSelect() {

	ARTSController* a = Cast<ARTSController>(GetWorld()->GetFirstPlayerController());
	a->conMesg();
}