// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Rock.h"


// Sets default values
ARock::ARock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Set Icon texture
	ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/Texture/Icons/RockIcon"));
	rockIcon = icon.Object;

	//Default mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));					//Create new mesh instance
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Resources/rock2"));		//get mesh
	mesh->SetStaticMesh(MeshObj.Object);

	//Outline material
	mesh->SetRenderCustomDepth(false);													//Outline show
	mesh->CustomDepthStencilValue = STENCIL_FRIENDLY_OUTLINE;

	//RootComponent = meesh;
	mesh->SetupAttachment(RootComponent);

}

// Called every frame
int ARock::harvest_Implementation(int amount)
{
	if (amount >= currStock) {
		int s = currStock;
		currStock = 0;
		this->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Rock Dead, But keep going"));
		return s;
	}
	else {
		currStock -= amount;
		return amount;
	}
}

// Called when the game starts or when spawned
void ARock::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Selection
void ARock::deSelect_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("deslected"));
	mesh->SetRenderCustomDepth(false);
}

void ARock::Select_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Selected"));
	mesh->SetRenderCustomDepth(true);
}

