 // Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/PatrolRouteComponent.h"

UPatrolRouteComponent* UChooseNextWaypoint::GetPatrolRouteComponent(AAIController* lAIController)
{
    if (lAIController)
    {
        APawn* pawn = lAIController->GetPawn();
        if (pawn)
        {
            return Cast<UPatrolRouteComponent>(pawn->GetComponentByClass(UPatrolRouteComponent::StaticClass()));
        }
    }
    return nullptr;
}

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto *patrolRouteComp = GetPatrolRouteComponent(OwnerComp.GetAIOwner());
    if (!ensure(patrolRouteComp))
    {
        return EBTNodeResult::Failed;
    }

    // Set Waypoint
    UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
    auto index = blackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    const auto &patrolRoute = patrolRouteComp->GetPatrolWaypoints();
    if(!ensure(patrolRoute.Num() > 0 && index >= 0 && index < patrolRoute.Num()))
    {
        return EBTNodeResult::Failed;
    }
    blackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, patrolRoute[index]);

    // Cycle next waypoint
    auto nextIndex = (index + 1) % patrolRoute.Num();
    blackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);

    return EBTNodeResult::Succeeded;
}