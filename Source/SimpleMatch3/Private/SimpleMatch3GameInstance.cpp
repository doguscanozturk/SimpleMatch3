#include "SimpleMatch3GameInstance.h"

void USimpleMatch3GameInstance::Init()
{
	Super::Init();

	BlueprintReferences = Cast<UBlueprintReferences>(BlueprintReferencesDataAsset);
	
	BasicMatch3ToolProvider = NewObject<UBasicMatch3ToolProvider>(this);
	BasicMatch3ToolProvider->Initialize(BlueprintReferences);
}

void USimpleMatch3GameInstance::Uninitialize()
{
	BlueprintReferences = nullptr;
	
	BasicMatch3ToolProvider->Uninitialize();
	BasicMatch3ToolProvider = nullptr;
}

void USimpleMatch3GameInstance::Clear()
{
	BasicMatch3ToolProvider->Clear();
}

void USimpleMatch3GameInstance::TriggerRestartClicked()
{
	OnRestartClicked.Broadcast();
}
