#include "BasicMatch3ToolProvider.h"

void UBasicMatch3ToolProvider::Initialize(const UBlueprintReferences* BlueprintReferences)
{
	BezierMovementManager = Cast<ABezierMovementManager>(GetWorld()->SpawnActor(ABezierMovementManager::StaticClass()));
	MatchFinder = NewObject<UMatchFinder>(this);
	MatchIdentifier = NewObject<UMatchIdentifier>(this);
	PieceGenerator = NewObject<UPieceGenerator>(this);
	PieceGenerator->Initialize(BlueprintReferences->PieceBP, Cast<UPieceVariations>(BlueprintReferences->PieceSettings));
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

	GEngine->ForceGarbageCollection();
}

void UBasicMatch3ToolProvider::Clear()
{
	BezierMovementManager->Clear();
}
