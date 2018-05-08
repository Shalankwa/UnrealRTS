// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Remo_V3.generated.h"

/*Definitions for AI state's
Odd numbers used for movement states*/
#define remoID 1
#define idle 0
#define movingToResource 1
#define harvesting 2
#define movingToRepair 3
#define repairing 4

UCLASS()
class MYPROJECT2_API ARemo_V3 : public ACharacter, public ISelectable, public IUnit
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARemo_V3();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int state = 0;
	float carryAmount = 0;
	int MAX_CARRY = 5;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(BlueprintReadWrite, Category = "Target")
		AActor* target;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* meesh;
	UPROPERTY(EditAnyWhere)
		UTexture2D* remoIcon;

	//Unit Overrides
	virtual void gather_Implementation(AActor* t) override;
	virtual void repair_Implementation(AActor* t) override;
	virtual void clearState_Implementation() override { state = 0; };

	//Selectable Overrides
	virtual void Select_Implementation() override;
	virtual void deSelect_Implementation() override;
	virtual UTexture2D* getIcon_Implementation() override { return remoIcon; };
	virtual int getID_Implementation() override { return remoID; };
	virtual int getHPStatus_Implementation() override { return 100; };


};