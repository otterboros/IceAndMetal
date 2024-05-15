// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IceAndMetalGameModeBase.h"
#include "DestroyAllEnemiesGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ICEANDMETAL_API ADestroyAllEnemiesGameMode : public AIceAndMetalGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
	
};
