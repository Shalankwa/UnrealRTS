// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Generator.generated.h"

#define generatorID 3

UCLASS()
class MYPROJECT2_API AGenerator : public AActor, public ISelectable, public Ibuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float generate = 0;

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
	virtual int getID_Implementation() override { return (status >= 100) ? generatorID : 0; };
	virtual int getHPStatus_Implementation() override { return status; };
};