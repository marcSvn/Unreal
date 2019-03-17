 // Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "Pawns/RoutePatrollerPawn.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    AAIController* controller = OwnerComp.GetAIOwner();
    if (!controller || !BlackboardComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Controller or BlackboardComp!"));
        return EBTNodeResult::Failed;
    }

    ARoutePatrollerPawn* routePatroller = Cast<ARoutePatrollerPawn>(controller->GetPawn());
    if (!routePatroller)
    {
        return EBTNodeResult::Failed;
    }

    const auto &patrolRoute = routePatroller->PatrolWaypoints;

    auto index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    if(!ensureMsgf(index >= 0 && index < patrolRoute.Num(), TEXT("Invalid index! %d"), index))
    {
        return EBTNodeResult::Failed;
    }

    AActor *currentWaypoint = patrolRoute[index];
    BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, currentWaypoint);

    auto nextIndex = (index + 1) % patrolRoute.Num();
    BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);

    return EBTNodeResult::Succeeded;
}