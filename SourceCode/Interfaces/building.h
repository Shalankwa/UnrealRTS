// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "building.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class Ubuilding : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class MYPROJECT2_API Ibuilding
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//Building placement
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "blocked")
		void blocked();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "unblocked")
		void unblocked();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "repair")
		void repair(int n);
	

};
