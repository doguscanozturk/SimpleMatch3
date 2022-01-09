#include "BasicMatch3ToolProvider.h"
#include "Match/InitialMatchRemover.h"

void UBasicMatch3ToolProvider::Initialize(UBlueprintReferences* BlueprintReferences)
{
	BezierMovementManager = Cast<ABezierMovementManager>(GetWorld()->SpawnActor(ABezierMovementManager::StaticClass()));
	MatchFinder = NewObject<UMatchFinder>(this);
	MatchIdentifier = NewObject<UMatchIdentifier>(this);
	PieceGenerator = NewObject<UPieceGenerator>(this);
	PieceGenerator->Initialize(BlueprintReferences->PieceBP, Cast<UPieceVariations>(BlueprintReferences->PieceSettings));
	GridGenerator = NewObject<UGridGenerator>(this);
	GridGenerator->Initialize(PieceGenerator, BlueprintReferences);
	InitialMatchRemover = NewObject<UInitialMatchRemover>(this);
	InitialMatchRemover->Initialize(this);
}

void UBasicMatch3ToolProvider::Uninitialize()
{
	PieceGenerator->Clear();
	PieceGenerator = nullptr;

	MatchIdentifier->Clear();
	MatchIdentifier = nullptr;
	
	MatchFinder->Clear();
	MatchFinder = nullptr;
	
	BezierMovementManager->Clear();
	BezierMovementManager->Destroy();
	BezierMovementManager = nullptr;
	
	InitialMatchRemover->Clear();
	InitialMatchRemover = nullptr;
	
	GridGenerator->Clear();
	GridGenerator = nullptr;

	GEngine->ForceGarbageCollection();
}

void UBasicMatch3ToolProvider::Clear() const
{
	BezierMovementManager->Clear();
}
