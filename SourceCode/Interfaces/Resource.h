// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resource.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UResource : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class MYPROJECT2_API IResource
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// Abstract Methods for Resources
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Harvest")
		int harvest(int amount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource Type")
		int getType();

};
