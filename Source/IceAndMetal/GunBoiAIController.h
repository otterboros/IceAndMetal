// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GunBoiAIController.generated.h"

/**
 * 
 */
UCLASS()
class ICEANDMETAL_API AGunBoiAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree;
	class UBlackboardComponent* BlackboardComponent;

	FName PlayerLocation = 	FName(TEXT("PlayerLocation"));
	FName StartLocation = 	FName(TEXT("StartLocation"));
	FName LastKnownPlayerLocation = FName(TEXT("LastKnownPlayerLocation"));

};
