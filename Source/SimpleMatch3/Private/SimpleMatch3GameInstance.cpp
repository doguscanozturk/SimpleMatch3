#include "SimpleMatch3GameInstance.h"

void USimpleMatch3GameInstance::Init()
{
	Super::Init();

	BlueprintReferences = Cast<UBlueprintReferences>(BlueprintReferencesDataAsset);
	
	BasicMatch3ToolProvider = NewObject<UBasicMatch3ToolProvider>(this);
	BasicMatch3ToolProvider->Initialize(BlueprintReferences);
}

void USimpleMatch3GameInstance::Clear()
{
	BlueprintReferences = nullptr;
	
	BasicMatch3ToolProvider->Clear();
	BasicMatch3ToolProvider = nullptr;
}

void USimpleMatch3GameInstance::TriggerRestartClicked()
{
	(void)OnRestartClicked.ExecuteIfBound();
}
