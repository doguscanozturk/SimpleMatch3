#include "UI/Match3UIManager.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "ThirdParty/boolinq.h"
#include "UI/LevelEndPanel.h"
#include "UI/TargetPanel.h"

void UMatch3UIManager::Initialize(UMatch3TargetManager* Match3TargetManager, UPieceVariations* pieceVariations)
{
	LoadPanels();

	PieceVariations = pieceVariations;

	Match3TargetManager->OnTargetsInitialized.AddUObject(this, &UMatch3UIManager::HandleTargetsInitialized);
	Match3TargetManager->OnATargetUpdated.AddUObject(this, &UMatch3UIManager::HandleATargetUpdated);
	Match3TargetManager->OnATargetComplete.AddUObject(this, &UMatch3UIManager::HandleATargetComplete);
	Match3TargetManager->OnAllTargetsComplete.AddUObject(this, &UMatch3UIManager::HandleAllTargetsComplete);
}

void UMatch3UIManager::Clear()
{
	PieceVariations = nullptr;

	TargetPanel->RemoveFromViewport();
	TargetPanel = nullptr;

	LevelEndPanel->RemoveFromViewport();
	LevelEndPanel = nullptr;
}

void UMatch3UIManager::LoadPanels()
{
	const FStringClassReference TargetPanelReference(TEXT("/Game/Blueprints/UI/TargetPanel.TargetPanel_C"));
	if (UClass* TargetPanelClass = TargetPanelReference.TryLoadClass<UUserWidget>())
	{
		TargetPanel = CreateWidget<UTargetPanel>(GetWorld()->GetGameInstance(), TargetPanelClass);

		if (TargetPanel)
		{
			TargetPanel->Initialize();
			TargetPanel->AddToViewport();
		}
	}

	const FStringClassReference LevelEndPanelReference(TEXT("/Game/Blueprints/UI/LevelEndPanel.LevelEndPanel_C"));
	if (UClass* LevelEndPanelClass = LevelEndPanelReference.TryLoadClass<UUserWidget>())
	{
		LevelEndPanel = CreateWidget<ULevelEndPanel>(GetWorld()->GetGameInstance(), LevelEndPanelClass);
	}
}

void UMatch3UIManager::HandleTargetsInitialized(const std::vector<UTargetData*> TargetDatas)
{
	for (int i = 0; i < TargetDatas.size(); ++i)
	{
		auto PieceDataTuple = PieceVariations->TryGetPieceData(PieceVariations->Variations, TargetDatas[i]->Type);
		const auto IsDataExist = std::get<bool>(PieceDataTuple);
		const auto PieceData = std::get<FPieceData>(PieceDataTuple);
		if (IsDataExist)
		{
			TargetPanel->TargetUIs[i]->InitializeType(TargetDatas[i]->Type, PieceData.Texture);
			TargetPanel->TargetUIs[i]->UpdateAmount(TargetDatas[i]->Amount);
		}
	}
}

void UMatch3UIManager::HandleATargetUpdated(const UTargetData* TargetData)
{
	const auto PieceDataTuple = PieceVariations->TryGetPieceData(PieceVariations->Variations, TargetData->Type);
	const auto IsDataExist = std::get<bool>(PieceDataTuple);
	const auto PieceData = std::get<FPieceData>(PieceDataTuple);

	if (!IsDataExist)
	{
		throw new std::exception("Target data is not exist!");
	}

	const auto TargetUI = TargetPanel->TryGetTargetUI(PieceData.Type);
	TargetUI->UpdateAmount(TargetData->Amount);
}

void UMatch3UIManager::HandleATargetComplete(const UTargetData* TargetData)
{
	const auto TargetUI = TargetPanel->TryGetTargetUI(TargetData->Type);
	TargetUI->SetCheckmarkActive(true);
}

void UMatch3UIManager::HandleAllTargetsComplete()
{
	TargetPanel->RemoveFromViewport();
	LevelEndPanel->AddToViewport();
}
