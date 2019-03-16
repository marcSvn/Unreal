 // Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    auto index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

    UE_LOG(LogTemp, Warning, TEXT("AI In c++! %d"), index);
    return EBTNodeResult::Succeeded;
}