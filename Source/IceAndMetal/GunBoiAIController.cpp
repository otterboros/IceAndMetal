// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBoiAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GunsBoi.h"


void AGunBoiAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehaviorTree != nullptr)
    {
        RunBehaviorTree(AIBehaviorTree);

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        BlackboardComponent = GetBlackboardComponent();

        BlackboardComponent->SetValueAsVector(StartLocation, GetPawn()->GetActorLocation());
    } 
}

void AGunBoiAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
bool AGunBoiAIController::IsDead() const
{
    AGunsBoi* AICharacter = Cast<AGunsBoi>(GetPawn());
    if(AICharacter != nullptr)
    {
        return AICharacter->IsDead();
    }
    return true;
}
