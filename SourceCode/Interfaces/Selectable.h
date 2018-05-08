// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Selectable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class USelectable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class MYPROJECT2_API ISelectable
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Abstract methods for all selectable actors
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Select")
		UTexture2D* getIcon();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Select")
		void Select();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "deSelect")
		void deSelect();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "unitID")
		int getID();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HP_Status")
		int getHPStatus();


};
