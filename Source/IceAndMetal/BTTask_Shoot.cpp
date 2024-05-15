// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "GunsBoi.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AGunsBoi* AIPawn = Cast<AGunsBoi>(OwnerComp.GetAIOwner()->GetPawn());

    if(AIPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    
    AIPawn->Shoot();

    return EBTNodeResult::Succeeded;
}