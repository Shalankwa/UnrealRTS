// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Remo_V3.h"


// Sets default values
ARemo_V3::ARemo_V3()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Icon texture
	ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/Texture/Icons/Remo_V3Icon"));
	remoIcon = icon.Object;

	//Default unit Size
	GetCapsuleComponent()->SetCapsuleSize(34, 88);

	//Default mesh

	meesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));					//Create new mesh instance
	meesh->SetMobility(EComponentMobility::Movable);									//Can move
	meesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);							//Wont collide with others
																						//meesh->SetCanEverAffectNavigation(false);											//Effects Nav
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/RemoBot_V3"));	//get mesh
	meesh->SetStaticMesh(MeshObj.Object);												//Set Mesh


																						//Outline material
	meesh->SetRenderCustomDepth(false);													//Outline show
	meesh->CustomDepthStencilValue = STENCIL_FRIENDLY_OUTLINE;							//colour set

																						//RootComponent = meesh;
	meesh->SetupAttachment(RootComponent);												//Attach to NPC:Remo_V3

																						//meesh->ComponentTags.Add("bot");
	this->Tags.Add("bot");
}

// Called when the game starts or when spawned
void ARemo_V3::BeginPlay()
{
	Super::BeginPlay();

	AIControllerClass = ABotController::StaticClass();
	this->SpawnDefaultController();

	//Somehow doesn't exist error
	if (GetController() != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Class = %s"), *GetController()->GetName());

}

//Selection
void ARemo_V3::deSelect_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("deslected"));
	meesh->SetRenderCustomDepth(false);
}

void ARemo_V3::Select_Implementation() {
	//UE_LOG(LogTemp, Warning, TEXT("Selected"));
	meesh->SetRenderCustomDepth(true);
}

//Gather Resources
void ARemo_V3::gather_Implementation(AActor* t) {
	UE_LOG(LogTemp, Warning, TEXT("Going"));
	this->target = t;
	//GetWorld()->GetNavigationSystem()->SimpleMoveToLocation(Controller, FVector(0, 0, 0));
	GetWorld()->GetNavigationSystem()->SimpleMoveToActor(Controller, t);
	state = movingToResource;
}

//Repair buildings
void ARemo_V3::repair_Implementation(AActor* t) {
	UE_LOG(LogTemp, Warning, TEXT("Going"));
	this->target = t;
	//GetWorld()->GetNavigationSystem()->SimpleMoveToLocation(Controller, FVector(0, 0, 0));
	GetWorld()->GetNavigationSystem()->SimpleMoveToActor(Controller, t);
	state = movingToRepair;
}

// Called every frame
void ARemo_V3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AAIController* brain = Cast<AAIController>(Controller);

	if (target != nullptr && target->IsPendingKill()) {
		target = nullptr;
		state = 0;
		UE_LOG(LogTemp, Warning, TEXT("Im free"));
	}

	//If we're mvoing to a target, and in distance
	if (state % 2 == 1 && this->GetDistanceTo(target) < 500) {
		UE_LOG(LogTemp, Warning, TEXT("At target"));
		//Swap to next action based on movement state
		switch (state) {
		case movingToResource:	state = harvesting;	break;
		case movingToRepair:	state = repairing;	break;
		}
		brain->StopMovement();
	}
	//Harvest while in distance
	if (state == harvesting) {
		carryAmount += (5 * DeltaTime);
		//UE_LOG(LogTemp, Warning, TEXT("Harvesting %f"), carryAmount);
		if (carryAmount >= MAX_CARRY) {

			IResource* t = Cast<IResource>(target);

			//Harvest from target Resource
			int x = (t)->Execute_harvest(target, carryAmount);

			//Send resource to player stock (Switch on Resouce type)
			switch (t->Execute_getType(target)) {
			case 1:
				(Cast<AMyCameraPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))->updateCurrentLiquid(x);
				break;
			case 2:
				(Cast<AMyCameraPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))->updateCurrentWood(x);
				break;
			case 3:
				(Cast<AMyCameraPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()))->updateCurrentMetal(x * 2);
				break;
			default:
				break;
			}
			carryAmount = 0;
		}
	}
	//Repairing while in distance
	if (state == repairing) {
		//int repairAmount += (5 * DeltaTime);
		Ibuilding* b = Cast<Ibuilding>(target);
		static float repairTimer = 0;
		repairTimer += DeltaTime;

		if (b && repairTimer > 1) {
			b->Execute_repair(target, 10);
			repairTimer = 0;
		}

	}


}

// Called to bind functionality to input
void ARemo_V3::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

