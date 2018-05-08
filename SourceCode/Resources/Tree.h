// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interfaces/Selectable.h"
#include "Interfaces/Resource.h"
#include "Tree.generated.h"

#define treeID 20

UCLASS()
class MYPROJECT2_API ATree : public AActor, public ISelectable, public IResource
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int currStock = 100;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;
	UPROPERTY(EditAnyWhere)
		UTexture2D* treeIcon;

	//Resource Overrides
	virtual int harvest_Implementation(int amount) override;
	virtual int getType_Implementation() override { return 2; };

	//Selectable Overrides
	virtual void Select_Implementation() override;
	virtual void deSelect_Implementation() override;
	virtual UTexture2D* getIcon_Implementation() override { return treeIcon; };
	virtual int getID_Implementation() override { return treeID; };
	virtual int getHPStatus_Implementation() override { return currStock; };
	
};
