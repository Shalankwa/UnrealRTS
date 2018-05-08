// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "icon.h"
#include "MyProject2GameModeBase.h"
#include "RTS_UI.h"
#include "Public/Incubator.h"
#include "Public/Generator.h"
#include "Public/Temple.h"
#include "Public/Spire.h"
#include "Public/SpawnFlag.h"
#include "Remo.h"
#include "Public/Remo_V2.h"
#include "Public/Remo_V3.h"
#include "Public/Remo_V4.h"
#include "RTSHUD.h"
#include "GameFramework/Pawn.h"
#include "MyCameraPawn.generated.h"

#define instanceOf(c, o)	Cast<c>(o)
#define print(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT(x));}
#define printC(x, c) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, c, TEXT(x));}

UCLASS()
class MYPROJECT2_API AMyCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCameraPawn();

	//Deselects all currently selected actors
	UFUNCTION(BlueprintCallable, Category = "Unselect")
		void unSelect();

	/* Accessor for Resource Wood*/
	UFUNCTION(BlueprintPure, Category = "Wood")
		int getCurrentWood();

	/* Accessor for Resource Liquid (Energy?)*/
	UFUNCTION(BlueprintPure, Category = "Liquid")
		int getCurrentLiquid();

	/* Accessor for Resource Metal (Rocks and minerals)*/
	UFUNCTION(BlueprintPure, Category = "Metal")
		int getCurrentMetal();

	/**Updates the Resource ____
	*@param x, takes a int, updates the resources by that value (-/+)
	*/
	UFUNCTION(BlueprintCallable, Category = "Wood")
		void updateCurrentWood(int x);

	UFUNCTION(BlueprintCallable, Category = "Wood")
		void updateCurrentLiquid(int x);

	UFUNCTION(BlueprintCallable, Category = "Wood")
		void updateCurrentMetal(int x);


	//Spawn a bot type = od, on selected incubator
	UFUNCTION(BlueprintCallable, Category = "Bot")
		void Spawn(int id);
	//(Testing)
		void Spawn() { Spawn(0); };

	//Create a building by given id
	UFUNCTION(BlueprintCallable, Category = "Bot")
		void build(int buildingID);

private:

	//Resources
	UPROPERTY(EditAnywhere, Category = "Wood") //current wood resource
		int CurrentWood = 100;
	UPROPERTY(EditAnywhere, Category = "Liquid") //current liquid resource
		int liquid = 100;
	UPROPERTY(EditAnywhere, Category = "Metal") //current Metal resource
		int metal = 100;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = bot)
		TSubclassOf<class ARemo> newRemo;

	//References to other Obj's
	UPROPERTY(EditAnywhere)
		USpringArmComponent* OurCameraSpringArm;
	UCameraComponent* OurCamera;
	APlayerController* mouse;
	ARTSHUD* gameHUD;


	//Stored selected Actors (units, buildings, resources, etc)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "units")
		TSet<AActor*> unitSelected;

	//Reference of building to place
	AActor* buildingToPlace;

	// cost of buildingToPlace: liquid, wood, metal
	int cost[3] = { 0,0,0 };

	//Input variables
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;
	bool multiSelect;
	bool bSelect;

	// bPlace[0] = if we are placing, bPlacing[1] if we cannot place
	bool bPlacing[2] = {false, false};
	
	//Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void ZoomIn();
	void ZoomOut();
	void click();
	void rightClick();
	void toggleMultiSelect();
	void togglebSelect();

	//Managing selected units list
	void addToUnitList(AActor* a);


//Default Unreal Functions
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
