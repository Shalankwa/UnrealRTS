// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Temple.h"


// Sets default values
ATemple::ATemple()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Set Icon texture
	ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/Texture/Icons/TempleIcon"));
	incIcon = icon.Object;

	//Default mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	//Setting all meshes for object
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> aMesh(TEXT("/Game/Buildings/Temple/TempleGhost"));
		mStatus.Add(aMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> bMesh(TEXT("/Game/Buildings/Temple/TempleStatus0"));
		mStatus.Add(bMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> cMesh(TEXT("/Game/Buildings/Temple/TempleStatus1"));
		mStatus.Add(cMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> dMesh(TEXT("/Game/Buildings/Temple/TempleStatus2"));
		mStatus.Add(dMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> eMesh(TEXT("/Game/Buildings/Temple/Temple"));
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
void ATemple::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATemple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Update Status
void ATemple::updateStatus(int n) {
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
void ATemple::blocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Lapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_ENEMY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}

void ATemple::unblocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("notLapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_FRIENDLY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}
//Selection
void ATemple::deSelect_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("deslected"));
	mesh->SetRenderCustomDepth(false);
}

void ATemple::Select_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Selected"));
	mesh->SetRenderCustomDepth(true);
}
