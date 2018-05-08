// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/building.h"
#include "Interfaces/Selectable.h"
#include "GameFramework/Actor.h"
#include "Spire.generated.h"

#define spireID 5

UCLASS()
class MYPROJECT2_API ASpire : public AActor, public ISelectable, public Ibuilding
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Mesh and icon reference
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;
	UPROPERTY(EditAnyWhere)
		UTexture2D* incIcon;

	//Building overrides? - make a new interface?
	UPROPERTY(EditAnyWhere, BlueprintReadonly, Category = "Status Hp")
		int status = 0;

	//Array of this ojects mesh's
	TArray<UStaticMesh*> mStatus;


	UFUNCTION(BlueprintCallable)
		void updateStatus(int i);


	//building Overrides
	virtual void blocked_Implementation() override;
	virtual void unblocked_Implementation() override;
	virtual void repair_Implementation(int n) override { updateStatus(n); };

	//Selectable Overrides
	virtual void Select_Implementation() override;
	virtual void deSelect_Implementation() override;
	virtual UTexture2D* getIcon_Implementation() override { return incIcon; };
	virtual int getID_Implementation() override { return (status >= 100) ? spireID : 0; };
	virtual int getHPStatus_Implementation() override { return status; };
};
