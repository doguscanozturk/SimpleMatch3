#include "Match3Initializer.h"
#include "Constants/UXConstants.h"
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

	TileGrid = GameInstance->BasicMatch3ToolProvider->GridGenerator->Generate(GridSize);
	GameInstance->BasicMatch3ToolProvider->InitialMatchRemover->RemoveInitialMatches(TileGrid);
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

	BoardFlowManager->Uninitialize();
	BoardFlowManager->Destroy();
	BoardFlowManager = nullptr;

	TargetManager->Clear();
	TargetManager = nullptr;

	UIManager->Clear();
	UIManager = nullptr;

	TileGrid->Clear();
	TileGrid = nullptr;

	GameInstance->Clear();

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

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AMatch3Initializer::Initialize,
		UXConstants::DelayBeforeInitializationWhenRestarting, false);
}
