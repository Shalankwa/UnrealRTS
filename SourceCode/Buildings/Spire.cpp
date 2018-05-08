// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Spire.h"


// Sets default values
ASpire::ASpire()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Set Icon texture
	ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/Texture/Icons/SpireIcon"));
	incIcon = icon.Object;

	//Default mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	//Setting all meshes for object
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> aMesh(TEXT("/Game/Buildings/Spire/SpireGhost"));
		mStatus.Add(aMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> bMesh(TEXT("/Game/Buildings/Spire/SpireStatus0"));
		mStatus.Add(bMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> cMesh(TEXT("/Game/Buildings/Spire/SpireStatus1"));
		mStatus.Add(cMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> dMesh(TEXT("/Game/Buildings/Spire/SpireStatus3"));
		mStatus.Add(dMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> eMesh(TEXT("/Game/Buildings/Spire/Spire"));
		mStatus.Add(eMesh.Object);
	}
	//Set default mesh
	mesh->SetStaticMesh(mStatus[0]);
	mesh->SetCollisionProfileName(TEXT("OverlapALL"));

	//Outline material
	mesh->SetRenderCustomDepth(false);													//Outline show
	mesh->CustomDepthStencilValue = STENCIL_FRIENDLY_OUTLINE;

	//RootComponent = meesh;
	mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASpire::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Update Status
void ASpire::updateStatus(int n) {
	//update the status with i
	status += n;

	if (status > 100) {
		status = 100;
	}

	if (status > 0 && status < 25) {
		//Get the building model
		mesh->SetStaticMesh(mStatus[1]);
		mesh->SetCollisionProfileName(TEXT("BlockAll"));
	}
	else if (status >= 25 && status < 50) {
		//Get the building model
		mesh->SetStaticMesh(mStatus[2]);
		mesh->SetCollisionProfileName(TEXT("BlockAll"));
	}
	else if (status >= 50 && status < 75) {
		//Get the building model
		mesh->SetStaticMesh(mStatus[3]);
		mesh->SetCollisionProfileName(TEXT("BlockAll"));
	}
	else if (status >= 100) {
		//Get the building model
		mesh->SetStaticMesh(mStatus[4]);
		mesh->SetCollisionProfileName(TEXT("BlockAll"));
	}

}
//Placement blocking 
void ASpire::blocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Lapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_ENEMY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}

void ASpire::unblocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("notLapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_FRIENDLY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}
//Selection
void ASpire::deSelect_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("deslected"));
	mesh->SetRenderCustomDepth(false);
}

void ASpire::Select_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Selected"));
	mesh->SetRenderCustomDepth(true);
}
