#pragma once
#include "CoreMinimal.h"
#include "BasicMatch3ToolProvider.h"
#include "Engine/GameInstance.h"
#include "DataAssets/BlueprintReferences.h"
#include "SimpleMatch3GameInstance.generated.h"

UCLASS()
class SIMPLEMATCH3_API USimpleMatch3GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBlueprintReferences* BlueprintReferences;

	UPROPERTY()
	UBasicMatch3ToolProvider* BasicMatch3ToolProvider;

	DECLARE_EVENT(USimpleMatch3GameInstance, FOnRestartClicked)
	FOnRestartClicked OnRestartClicked;

private:
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void Clear();
	
	UFUNCTION(BlueprintCallable)
	void TriggerRestartClicked();
	
	UPROPERTY(EditAnywhere)
	UDataAsset* BlueprintReferencesDataAsset;
};
