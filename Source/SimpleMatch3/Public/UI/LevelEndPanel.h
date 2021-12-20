#pragma once
#include "Blueprint/UserWidget.h"
#include "LevelEndPanel.generated.h"

UCLASS()
class ULevelEndPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
};
