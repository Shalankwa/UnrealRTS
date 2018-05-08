// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Rock.generated.h"

#define rockID 21

UCLASS()
class MYPROJECT2_API ARock : public AActor, public ISelectable, public IResource
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int currStock = 200;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;
	UPROPERTY(EditAnyWhere)
		UTexture2D* rockIcon;

	//Resource Overrides
	virtual int harvest_Implementation(int amount) override;
	virtual int getType_Implementation() override { return 3; };

	//Selectable Overrides
	virtual void Select_Implementation() override;
	virtual void deSelect_Implementation() override;
	virtual UTexture2D* getIcon_Implementation() override { return rockIcon; };
	virtual int getID_Implementation() override { return rockID; };
	virtual int getHPStatus_Implementation() override { return currStock; };

};

