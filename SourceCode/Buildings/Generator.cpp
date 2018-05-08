// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Generator.h"


// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Icon texture
	ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/Texture/Icons/GeneratorIcon"));
	incIcon = icon.Object;

	//Default mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	//Setting all meshes for object
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> aMesh(TEXT("/Game/Buildings/Generator/GeneratorGhost"));
		mStatus.Add(aMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> bMesh(TEXT("/Game/Buildings/Generator/GeneratorStatus0"));
		mStatus.Add(bMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> cMesh(TEXT("/Game/Buildings/Generator/GeneratorStatus1"));
		mStatus.Add(cMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> dMesh(TEXT("/Game/Buildings/Generator/GeneratorStatus2"));
		mStatus.Add(dMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> eMesh(TEXT("/Game/Buildings/Generator/Generator"));
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
void AGenerator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Generate Liquid (energy) every 25 seconds (+25);
	if (status >= 100) {
		generate += 1 * DeltaTime;
	}
	
	if (generate >= 25) {
		(Cast<AMyCameraPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))->updateCurrentLiquid(generate);
		generate = 0;
	}

}

//Update Status
void AGenerator::updateStatus(int i) {
	//update the status with i
	status += i;

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
void AGenerator::blocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Lapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_ENEMY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}

void AGenerator::unblocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("notLapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_FRIENDLY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}
//Selection
void AGenerator::deSelect_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("deslected"));
	mesh->SetRenderCustomDepth(false);
}

void AGenerator::Select_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Selected"));
	mesh->SetRenderCustomDepth(true);
}

