// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTSController.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"
#include "icon.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API Uicon : public UUserWidget
{
	GENERATED_BODY()

protected:
	/*Holds a reference to the icon*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* iconTexture;
	
public:

	/*Sets the item texture*/
	UFUNCTION(BlueprintCallable, Category = UI)
		void SetIconTexture(UTexture2D* unit);

	UFUNCTION(BlueprintCallable, Category = UI)
		void setOnclick();

	UButton* iconButton;

	UFUNCTION()
	void Message();

	UFUNCTION()
	void unSelect();
};
