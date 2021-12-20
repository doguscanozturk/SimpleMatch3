#pragma once
#include "UI/TargetUI.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Pieces/PieceType.h"
#include "TargetPanel.generated.h"

UCLASS()
class SIMPLEMATCH3_API UTargetPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	uint8 TargetUICount;
	
	UPROPERTY(VisibleAnywhere)
	TArray<UTargetUI*> TargetUIs;
	
	virtual bool Initialize() override;
	
	UTargetUI* TryGetTargetUI(EPieceType Type);
};
