#pragma once
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Pieces/PieceType.h"
#include "TargetUI.generated.h"

UCLASS()
class UTargetUI : public UObject
{
	GENERATED_BODY()
	
public:
	void InitializeComponents(UImage* Icon, UTextBlock* Amount, UImage* Checkmark);
	
	void InitializeType(EPieceType PieceType, UTexture2D* Texture);
	
	void UpdateAmount(int UpdatedAmount);
	
	void SetVisibility(bool IsVisible);
	
	void SetCheckmarkActive(bool IsActive);

	UPROPERTY()
	EPieceType MType;
	
protected:
	UPROPERTY()
	UImage* MIcon;
	
	UPROPERTY()
	UTextBlock* MAmount;
	
	UPROPERTY()
	UImage* MCheckmark;
};
