// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyAllEnemiesGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "GunBoiAIController.h"


void ADestroyAllEnemiesGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (AGunBoiAIController* AIController : TActorRange<AGunBoiAIController>(GetWorld()))
    {
        if(!AIController->IsDead())
        {
            return;
        }
    }

    EndGame(true);
}

void ADestroyAllEnemiesGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
