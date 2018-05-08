// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "icon.h"
#include "Blueprint/UserWidget.h"
#include "RTS_UI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API URTS_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
		void setSelected();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
		void clearSelected();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
		Uicon* addIcon();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
		void swapActionBar(int id);
};
