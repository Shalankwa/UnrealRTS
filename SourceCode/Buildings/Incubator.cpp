// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Incubator.h"


// Sets default values
AIncubator::AIncubator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Icon texture
	ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/Texture/Icons/IncubatorIcon"));
	incIcon = icon.Object;

	//Default mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));			

	//Setting all meshes for object
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> aMesh(TEXT("/Game/Buildings/Incubator/IncubatorGhost"));
		mStatus.Add(aMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> bMesh(TEXT("/Game/Buildings/Incubator/IncubatorStatus0"));
		mStatus.Add(bMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> cMesh(TEXT("/Game/Buildings/Incubator/IncubatorStatus1"));
		mStatus.Add(cMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> dMesh(TEXT("/Game/Buildings/Incubator/IncubatorStatus2"));
		mStatus.Add(dMesh.Object);
		ConstructorHelpers::FObjectFinder<UStaticMesh> eMesh(TEXT("/Game/Buildings/Incubator/Incubator"));
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
void AIncubator::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AIncubator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

} 

//Update Status
void AIncubator::updateStatus(int n) {
	//update the status with i
	status += n;

	if (status > 100) {
		status = 100;
	}

	if (status > 0 && status < 25) {
		//Get the building model
		spawnAt = GetActorLocation() + FVector(-500.0f, 0.0f, 0.0f);
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

//Spawn unit
void AIncubator::spawnUnit(int id) {

	FVector Location = GetActorLocation();
	Location += FVector(0.0f, 200.0f, 0.0f); //offset spawn location
	
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters spIn;

	switch (id) {
	case 1:
		GetWorld()->SpawnActor<ARemo>(ARemo::StaticClass(), Location, Rotation, spIn);
		break;
	case 2:
		//GetWorld()->SpawnActor<ARemo_V2>(ARemo_V2::StaticClass(), Location, Rotation, spIn);
		break;
	case 3:
		break;
	case 4:
		break;
	}
	

}

//Placement blocking 
void AIncubator::blocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Lapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_ENEMY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}

void AIncubator::unblocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("notLapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_FRIENDLY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}
//Selection
void AIncubator::deSelect_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("deslected"));
	mesh->SetRenderCustomDepth(false);
}

void AIncubator::Select_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Selected"));
	mesh->SetRenderCustomDepth(true);
}
