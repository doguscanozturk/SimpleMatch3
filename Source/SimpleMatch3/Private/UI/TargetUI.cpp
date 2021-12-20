#include "UI/TargetUI.h"

void UTargetUI::InitializeComponents(UImage* Icon, UTextBlock* Amount, UImage* Checkmark)
{
	MIcon = Icon;
	MAmount = Amount;
	MCheckmark = Checkmark;
}

void UTargetUI::InitializeType(EPieceType PieceType, UTexture2D* Texture)
{
	MType = PieceType;
	MIcon->SetBrushFromTexture(Texture);
}

void UTargetUI::UpdateAmount(const int UpdatedAmount)
{
	MAmount->SetText(FText::FromString(FString::FromInt(UpdatedAmount)));
}

void UTargetUI::SetVisibility(const bool IsVisible)
{
	const auto ScaleValue = IsVisible ? FVector2D::ZeroVector : FVector2D::UnitVector;
	MIcon->SetRenderScale(ScaleValue);
	MAmount->SetRenderScale(ScaleValue);
	MCheckmark->SetRenderScale(ScaleValue);
}

void UTargetUI::SetCheckmarkActive(const bool IsActive)
{
	MAmount->SetRenderScale(IsActive ? FVector2D::ZeroVector : FVector2D::UnitVector);
	MCheckmark->SetRenderScale(IsActive ? FVector2D::UnitVector : FVector2D::ZeroVector);
}
