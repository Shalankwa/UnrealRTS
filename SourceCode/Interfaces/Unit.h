// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnit : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class MYPROJECT2_API IUnit
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//Abstract methods for all units
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "gather")
		void gather(AActor* target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "build")
		void repair(AActor* target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "resetState")
		void clearState();
};
