// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "SpawnFlag.h"


// Sets default values
ASpawnFlag::ASpawnFlag()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Set Icon texture
	ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/Texture/Icons/RemoIcon"));
	incIcon = icon.Object;

	//Default mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	//Setting all meshes for object
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> aMesh(TEXT("/Game/Buildings/spawnFlag"));
		mStatus.Add(aMesh.Object);

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
void ASpawnFlag::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpawnFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Placement blocking 
void ASpawnFlag::blocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Lapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_ENEMY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}

void ASpawnFlag::unblocked_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("notLapping"));
	mesh->SetRenderCustomDepth(false);
	mesh->CustomDepthStencilValue = STENCIL_FRIENDLY_OUTLINE;
	mesh->SetRenderCustomDepth(true);
}
//Selection
void ASpawnFlag::deSelect_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("deslected"));
	mesh->SetRenderCustomDepth(false);
}

void ASpawnFlag::Select_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Selected"));
	mesh->SetRenderCustomDepth(true);
}
