// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleMatch3GameModeBase.generated.h"


UCLASS()
class SIMPLEMATCH3_API ASimpleMatch3GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;
	
	virtual void BeginPlay() override;
};
