// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "MyCameraPawn.h"


// Sets default values
AMyCameraPawn::AMyCameraPawn()
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 2000.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;
	OurCameraSpringArm->bDoCollisionTest = false;

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	//Default Location
	SetActorLocation(FVector(0, 0, 0));
	SetActorRotation(FRotator(0, 0, 0));

	//Show Mouse
	mouse = Cast<APlayerController>(GetController());
	if (mouse)
	{
		gameHUD = Cast<ARTSHUD>(mouse->GetHUD());
		mouse->bShowMouseCursor = true;
		mouse->bEnableClickEvents = true;
		mouse->bEnableMouseOverEvents = true;
	}

	//Set Tag for getting
	this->Tags.Add("Controller");
}

// Called every frame
void AMyCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//When Placing a building
	{
		if (bPlacing[0]) {
			//Get where the cursor is pointing(only on the ground, channel1)
			FHitResult hit(ForceInit);
			mouse->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, hit);
			//mouse->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, hit);		//Hits any object
			FVector v = hit.Location;

			buildingToPlace->SetActorLocation(v);

			//Check iff overlapping
			{
				Ibuilding* isBuilding = Cast<Ibuilding>(buildingToPlace);
				
				//overlapping actors array
				TArray <AActor*> laps;
				buildingToPlace->GetOverlappingActors(laps);

				if (laps.Num() > 0) {
					bPlacing[1] = true;
					isBuilding->Execute_blocked(buildingToPlace);
				} else {
					bPlacing[1] = false;
					isBuilding->Execute_unblocked(buildingToPlace);
				}
					
			}

			//Check if moving a flag - keep within distance
			//TODO - Refactor
			{
				if (instanceOf(ASpawnFlag, buildingToPlace)) {
					if (unitSelected.Num() <= 0) {
						bPlacing[0] = false;
						buildingToPlace->Destroy();
					}
					else {
						AIncubator* i = Cast<AIncubator>(unitSelected.Array()[0]);

						if (i->GetDistanceTo(buildingToPlace) > 800) {
							bPlacing[1] = true;
							Cast<Ibuilding>(buildingToPlace)->Execute_blocked(buildingToPlace);
						}
					}
				}
			}
			
		}
	} // end placing

	//Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!MovementInput.IsZero())
		{
			//Scale our movement input axis values by 2000 units per second
			MovementInput *= 2000.0f;

			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);

		}
	}
}

// Called to bind functionality to input
void AMyCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMyCameraPawn::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMyCameraPawn::ZoomOut);

	//Click events
	InputComponent->BindAction("mLeft", IE_Pressed, this, &AMyCameraPawn::click);
	InputComponent->BindAction("rightClick", IE_Pressed, this, &AMyCameraPawn::rightClick);

	//Multi Select toggle
	InputComponent->BindAction("multiSelect", IE_Pressed, this, &AMyCameraPawn::toggleMultiSelect);
	InputComponent->BindAction("multiSelect", IE_Released, this, &AMyCameraPawn::toggleMultiSelect);

	//Multi Select Box
	InputComponent->BindAction("sBox", IE_Pressed, this, &AMyCameraPawn::togglebSelect);
	InputComponent->BindAction("sBox", IE_Released, this, &AMyCameraPawn::togglebSelect);

	//Movement up-down-left-right
	InputComponent->BindAxis("up/down", this, &AMyCameraPawn::MoveForward);
	InputComponent->BindAxis("left/right", this, &AMyCameraPawn::MoveRight);

	//Other events
	InputComponent->BindAction("Spawn", IE_Pressed, this, &AMyCameraPawn::Spawn);
}

//Up and Down
void AMyCameraPawn::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	//Clamp is a safty to ensure in range
}

//Left and right
void AMyCameraPawn::MoveRight(float AxisValue)
{
	MovementInput.Y = AxisValue;
}

/**	Toggle multi select
*	
*@requires: Lshift down, Lshift released
*/
void AMyCameraPawn::toggleMultiSelect() {
	multiSelect = ((multiSelect) ? false : true);
}

/**	Toggle selection box
*	
*	True:
*		Turn on selection box within HUD
*
*	False:
*		Get all actors under drawn box, select(a) 
*/
void AMyCameraPawn::togglebSelect() {
	bSelect = ((bSelect) ? false : true);	//toggle

	// Turn on box drawing
	gameHUD->setDrawBox(bSelect);

	// Select actors under drawn box
	if (!bSelect) {
		TArray<ACharacter*> boxSelectedUnit = gameHUD->boxHitActors();
		
		for (ACharacter* a : boxSelectedUnit ) {
			addToUnitList(Cast<AActor>(a));
		}

	}

}

/**	Left click		- TODO - Section off segments into other methods
*	Outcomes:
*
*	if placing, finalize placement
*	if hit a Actor, select(a)
*	nothing hit, unSelect()
*/
void AMyCameraPawn::click()
{
	//if we are placing and we clicked, place the building don't continue
	if (bPlacing[0]) {
		if (bPlacing[1]) {
			// Blocked!
			printC("Cannot place here.", FColor::Red)
			return;
		}

		//if placing a spawn flag, not a building
		if (instanceOf(ASpawnFlag, buildingToPlace)) {
			AIncubator* i = Cast<AIncubator>(unitSelected.Array()[0]);
			i->setSpawnAt(buildingToPlace->GetActorLocation());
			buildingToPlace->Destroy();
			bPlacing[0] = false;
			return;
		}

		//Deplete recourses by cost
		liquid -= cost[0];
		CurrentWood -= cost[1];
		metal -= cost[2];

		//Stop placing
		bPlacing[0] = false;

		//set building to first stage
		Ibuilding* isBuilding = Cast<Ibuilding>(buildingToPlace);
		isBuilding->Execute_repair(buildingToPlace, 1);
		
		//Unhighlight the building
		ISelectable* canSelect = Cast<ISelectable>(buildingToPlace);
		canSelect->Execute_deSelect(buildingToPlace);
		return;
	}

	//Getting where / what we hit
	FHitResult TraceResult(ForceInit);
	mouse->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, TraceResult);

	//If we hit something, and it is selectable
	if (TraceResult.GetActor() != nullptr && Cast<ISelectable>(TraceResult.GetActor())) {
		AActor *a = (TraceResult.GetActor());
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *a->GetName());
		//Select Multiple if holding shift
		if (multiSelect) {
			addToUnitList(a);
		}
		else { //unslect others, select hit
			unSelect();
			addToUnitList(a);
		}
		
	}
	else { //delect if hit nothing
		unSelect();
	}
}

// Add To Selected units set
void AMyCameraPawn::addToUnitList(AActor* a) {
	ISelectable* canSelect = Cast<ISelectable>(a);

	// If the actor we are looking to select is selectable...
	if (canSelect) {
		// If this is the first slected unit, set the actionbar
		if (unitSelected.Num() == 0) {
			//getUI and call swapActionBars depending on added element
			Cast<AMyProject2GameModeBase>(GetWorld()->GetAuthGameMode())->getUI()->swapActionBar(canSelect->getID_Implementation());
		}

		canSelect->Execute_Select(a);

		//Check if already added to Unit list
		bool inSet;
		unitSelected.Add(a, &inSet);
		
		if(!inSet){
			// add unit icon to selected units UI
			AMyProject2GameModeBase* GM = Cast<AMyProject2GameModeBase>(GetWorld()->GetAuthGameMode());
			Uicon* newIC = GM->getUI()->addIcon();
			newIC->iconButton->OnClicked.AddDynamic(this, &AMyCameraPawn::unSelect);
			newIC->SetIconTexture(canSelect->Execute_getIcon(a));
		}
		
	}
}

// unSelect selected units
void AMyCameraPawn::unSelect() {

	// Re-set actionbar to nothing
	Cast<AMyProject2GameModeBase>(GetWorld()->GetAuthGameMode())->getUI()->swapActionBar(0);

	{ //Clear Selected Icons
		AMyProject2GameModeBase* GM = Cast<AMyProject2GameModeBase>(GetWorld()->GetAuthGameMode());
		GM->getUI()->clearSelected();
	}

	//For all selected units, deSelect (turn off outline)
	for (AActor* s : unitSelected) {
		ISelectable* canSelect = Cast<ISelectable>(s);

		if(canSelect)
			canSelect->Execute_deSelect(s);
	}
	//empty selected unit list
	unitSelected.Empty();
}

/**	Right click		- TODO - Section off segments into other methods
*	Outcomes:
*
*	if placing, cancel placement	
*	if hit a building, send units to repair
*	if hit a resource, send units to collect
*	Send bots to location
*/
void AMyCameraPawn::rightClick() {

	//If placing a building, stop placing and detroy the Ghost
	if (bPlacing[0]) {
		bPlacing[0] = false;
		buildingToPlace->Destroy();
		return;
	}

	//Cursor Hit Result
	FHitResult hit(ForceInit);
	mouse->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, hit);
	FVector v = hit.Location;
	
	
	//If we hit a resource
	if (Cast<IResource>(hit.GetActor())) {
		UE_LOG(LogTemp, Warning, TEXT("Go harvest"));

		//Send all units to collect resource
		for (AActor* a : unitSelected) {
			IUnit* m = Cast<IUnit>(a);

			if (m) {
				m->clearState_Implementation();
				m->gather_Implementation(hit.GetActor());
			}
		}
		return;
	}

	//If we hit a building
	if (Cast<Ibuilding>(hit.GetActor())) {
		UE_LOG(LogTemp, Warning, TEXT("Go repair/Build"));

		for (AActor* a : unitSelected) {
			IUnit* m = Cast<IUnit>(a);

			if (m) {
				m->clearState_Implementation();
				m->repair_Implementation(hit.GetActor());
			}
		}
		return;
	}

	/**
	* Move all selected units to location in a grid
	*/
	{
		int amount = unitSelected.Num();
		int rowSize = sqrt(amount);
		int rowC = 0, colC = 0;

		for (AActor* a : unitSelected) {
			//If cur actor is not a Unit, go to next selected
			ACharacter* m = Cast<ACharacter>(a);

			if (m) {
				FVector displacement = FVector((150 * rowC), (150 * colC++), 0);

				//Clear the Bots current state, and move them
				Cast<IUnit>(m)->clearState_Implementation();
				GetWorld()->GetNavigationSystem()->SimpleMoveToLocation(m->GetController(), (v + displacement));

				if (colC >= rowSize) {
					colC = 0;
					rowC++;
				}
			}
		}
	}
}

/**Spawn Remo bot via ID
*
*@requires: first selected element must be a incubator
*@param id: id = what bot to spawn (1 - 4)
*/
void AMyCameraPawn::Spawn(int id) {
	
	FVector Location;
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters spIn;

	//Testing feature (used to cheat in a bot)
	if (id == 0) {
		Location = GetActorLocation();
		GetWorld()->SpawnActor<ARemo>(ARemo::StaticClass(), Location, Rotation, spIn);
		return;
	}

	//Get the first actor (Must be a incubator)
	AIncubator* i = Cast<AIncubator>(unitSelected.Array()[0]);
	Location = i->getSpawnAt();
	Location += FVector(0.0f, 0.0f, 20.0f); //offset spawn location

	// Determine bot type and cost (TODO - cost)
	AActor* a = nullptr;
	switch (id) {
	case 1:
		a = GetWorld()->SpawnActor<ARemo>(ARemo::StaticClass(), Location, Rotation, spIn);
		break;
	case 2:
		a = GetWorld()->SpawnActor<ARemo_V2>(ARemo_V2::StaticClass(), Location, Rotation, spIn);
		break;
	case 3:
		a = GetWorld()->SpawnActor<ARemo_V3>(ARemo_V3::StaticClass(), Location, Rotation, spIn);
		break;
	case 4:
		a = GetWorld()->SpawnActor<ARemo_V4>(ARemo_V4::StaticClass(), Location, Rotation, spIn);
		break;
	}

	// If spawn failed, report to user
	if (!a) {
		print("Failed spawn");
		return;
	}
	//TODO - else pay for cost

}

/**Spawn buildingt via ID
*
*@requires: first selected element must be a bot
*@param id: id = what building to place (1 - 4)
*/
void AMyCameraPawn::build(int buildingID) {
	
	if (bPlacing[0]) {
		//Report currently building
		print("Already building");
		return;
	}

	//Set spawn location to camera center
	FVector Location = GetActorLocation();
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters spIn;

	// Determine building and resource cost based on ID
	switch (buildingID) {
		//Placing Flag
		case 0:
			buildingToPlace = GetWorld()->SpawnActor<ASpawnFlag>(ASpawnFlag::StaticClass(), Location, Rotation, spIn);
			cost[0] = 0;
			cost[1] = 0;
			cost[2] = 0;
			break;
		case incubatorID: 
			if (CurrentWood < 50 || metal < 75) {
				//Report insuficiant rescources
				print("Requires: 50 organic, 75 metal");
				printC("Not enough resources", FColor::Red);
				return;
			}
			cost[0] = 0;
			cost[1] = 50;
			cost[2] = 75;
			buildingToPlace = GetWorld()->SpawnActor<AIncubator>(AIncubator::StaticClass(), Location, Rotation, spIn);
			break;
		case generatorID:
			if (CurrentWood < 10 || metal < 25) {
				//Report insuficiant rescources
				print("Requires: 10 organic, 25 metal");
				printC("Not enough resources", FColor::Red);
				return;
			}
			cost[0] = 0;
			cost[1] = 10;
			cost[2] = 25;
			buildingToPlace = GetWorld()->SpawnActor<AGenerator>(AGenerator::StaticClass(), Location, Rotation, spIn);
			break;
		case templeID:
			if (liquid < 50 || CurrentWood < 50 || metal < 10) {
				//Report insuficiant rescources
				print("Requires: 50 energy, 50 organic, 10 metal");
				printC("Not enough resources", FColor::Red);
				return;
			}
			cost[0] = 50;
			cost[1] = 50;
			cost[2] = 10;
			buildingToPlace = GetWorld()->SpawnActor<ATemple>(ATemple::StaticClass(), Location, Rotation, spIn);
			break;
		case spireID:
			if (liquid < 20 || CurrentWood < 20 || metal < 50) {
				//Report insuficiant rescources
				print("Requires: 20 energy, 20 organic, 50 metal");
				printC("Not enough resources", FColor::Red);
				return;
			}
			cost[0] = 20;
			cost[1] = 20;
			cost[2] = 50;
			buildingToPlace = GetWorld()->SpawnActor<ASpire>(ASpire::StaticClass(), Location, Rotation, spIn);
			break;
		default: 
			return;
	}
	
	//Set Placing to true
	bPlacing[0] = true;
}

//Zoom functions
void AMyCameraPawn::ZoomIn()
{
	//If we are placing a building, instead rotate building
	if (bPlacing[0]) {
		FRotator r = buildingToPlace->GetActorRotation();
		r.Yaw -= 5;
		buildingToPlace->SetActorRotation(r);
		return;
	}

	// Change camera vision area
	ZoomFactor += 0.02;
	OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(2000.0f, 300.0f, ZoomFactor);
}

void AMyCameraPawn::ZoomOut()
{
	//If we are placing a building, instead rotate building
	if (bPlacing[0]) {
		FRotator r = buildingToPlace->GetActorRotation();
		r.Yaw += 5;
		buildingToPlace->SetActorRotation(r);
		return;
	}

	// Change camera vision area
	ZoomFactor -= 0.02;
	OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(2000.0f, 300.0f, ZoomFactor);
}

//Accessors
int AMyCameraPawn::getCurrentWood()
{
	return CurrentWood;
}

int AMyCameraPawn::getCurrentLiquid()
{
	return liquid;
}

int AMyCameraPawn::getCurrentMetal()
{
	return metal;
}

//Update Resource amounts (Call by bots during harvest)
void AMyCameraPawn::updateCurrentWood(int x)
{
	CurrentWood += x;
}

void AMyCameraPawn::updateCurrentLiquid(int x)
{
	liquid += x;
}

void AMyCameraPawn::updateCurrentMetal(int x)
{
	metal += x;
}
