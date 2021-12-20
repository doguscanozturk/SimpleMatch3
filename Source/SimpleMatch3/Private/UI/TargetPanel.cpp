#include "UI/TargetPanel.h"

#include "Blueprint/WidgetTree.h"

bool UTargetPanel::Initialize()
{
	Super::Initialize();

	TargetUIs.Empty();

	for (int i = 1; i <= TargetUICount; ++i)
	{
		auto NewTargetUI = NewObject<UTargetUI>();

		FString IconName("Icon_");
		IconName.AppendInt(i);
		const auto IconImage = static_cast<UImage*>(WidgetTree->FindWidget(FName(IconName)));

		FString AmountName("Amount_");
		AmountName.AppendInt(i);
		const auto AmountText = static_cast<UTextBlock*>(WidgetTree->FindWidget(FName(AmountName)));

		FString CheckmarkName("Checkmark_");
		CheckmarkName.AppendInt(i);
		const auto CheckmarkImage = static_cast<UImage*>(WidgetTree->FindWidget(FName(CheckmarkName)));

		NewTargetUI->InitializeComponents(IconImage, AmountText, CheckmarkImage);

		TargetUIs.Add(NewTargetUI);
	}

	return true;
}

UTargetUI* UTargetPanel::TryGetTargetUI(EPieceType Type)
{
	UTargetUI* const* TAU = TargetUIs.FindByPredicate([&Type](const UTargetUI* TargetUI)
	{
		return TargetUI->MType == Type;
	});

	if(!TAU)
	{
		throw new std::exception("Can't find the requested target ui.");
	}

	return Cast<UTargetUI>(*TAU);
}
