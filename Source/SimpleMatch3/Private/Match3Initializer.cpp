#include "Match3Initializer.h"
#include "Controllers/GridController.h"
#include "Engine/AssetManager.h"
#include "Grid/GridGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/CameraHelpers.h"

AMatch3Initializer::AMatch3Initializer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMatch3Initializer::Initialize()
{
	IsInitialized = true;

	GridGenerator = NewObject<UGridGenerator>(this);
	GridGenerator->Initialize(GameInstance->BasicMatch3ToolProvider->PieceGenerator, GameInstance->BlueprintReferences);

	InitialMatchRemover = NewObject<UInitialMatchRemover>(this);
	InitialMatchRemover->Initialize(GameInstance->BasicMatch3ToolProvider);

	TileGrid = GridGenerator->Generate(GridSize);
	InitialMatchRemover->RemoveInitialMatches(TileGrid);
	CameraHelpers::PlaceCameraToTheCenterOfTheGrid(TileGrid, MainCamera);

	BoardFlowManager = Cast<ABoardFlowManager>(GetWorld()->SpawnActor(GameInstance->BlueprintReferences->BoardFlowManagerBP));
	BoardFlowManager->Initialize(TileGrid, GameInstance->BasicMatch3ToolProvider, GridController);

	TargetManager = NewObject<UMatch3TargetManager>();
	TargetManager->Initialize(BoardFlowManager);

	UIManager = NewObject<UMatch3UIManager>(this);
	UIManager->Initialize(TargetManager, Cast<UPieceVariations>(GameInstance->BlueprintReferences->PieceSettings));

	TargetManager->LoadRandomTargets();
}

void AMatch3Initializer::Uninitialize()
{
	IsInitialized = false;

	TargetManager->Clear();
	TargetManager = nullptr;

	UIManager->Clear();
	UIManager = nullptr;

	BoardFlowManager->Clear();
	BoardFlowManager->Destroy();
	BoardFlowManager = nullptr;

	TileGrid->Clear();
	TileGrid = nullptr;

	InitialMatchRemover->Clear();
	InitialMatchRemover = nullptr;

	GridGenerator->Clear();
	GridGenerator = nullptr;
	
	GEngine->ForceGarbageCollection();
}


void AMatch3Initializer::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<USimpleMatch3GameInstance>(GetGameInstance());
	GameInstance->OnRestartClicked.AddUObject(this, &AMatch3Initializer::HandleRestartClicked);

	GridController = Cast<AGridController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GridController->SetViewTargetWithBlend(MainCamera);
	
	Initialize();
}

void AMatch3Initializer::HandleRestartClicked()
{
	Uninitialize();

	Initialize();
}