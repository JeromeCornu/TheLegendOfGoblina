// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrolController.h"
#include "AIPatrol.h"
#include "PlayableCharacter.h"
#include "StandItem.h"
#include "SpawnVolume.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Result of beeing see + connection with the BB and the BT
AAIPatrolController::AAIPatrolController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

	// Initialize blackboard keys
	PlayerKey = "Player";
	PossessFoodKey = "PossessFood";
	InvestigateLocationKey = "InvestigateLocation";
	ExitKey = "Exit"; 
	IsPatrollingKey = "IsPatrolling";

	bIsPatrolling = false;
	PlateIndex = -1;	
}

void AAIPatrolController::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAIPatrolController::OnSee);
}

void AAIPatrolController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ExitActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnVolume::StaticClass());

	// Initialize the BehaviorTree's value : PossessMeat
	bool bValue = true;
	AAIPatrol* AICharacter = Cast<AAIPatrol>(InPawn);

	if (AICharacter)
	{
		// Populate patrol point array (make an array with all point that are in the game)
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStandItem::StaticClass(), Plates);
		
		RunBehaviorTree(AICharacter->BehaviorTree);

		// Set the variables of the BT
		Blackboard->SetValueAsObject(ExitKey, ExitActor);
		Blackboard->SetValueAsBool(PossessFoodKey, !bIsPatrolling);
		Blackboard->SetValueAsBool(IsPatrollingKey, bIsPatrolling);
	}		
}

// The player has been seen -> set a key on the blackboard
void AAIPatrolController::OnSee(AActor* Actor, FAIStimulus Stimulus)
{
	APlayableCharacter* Target = Cast<APlayableCharacter>(Actor);

	if (Blackboard && Target) 
	{
		if (Blackboard->GetValueAsObject(PlayerKey))
		{
			Blackboard->SetValueAsVector(InvestigateLocationKey, Target->GetActorLocation());
			Blackboard->ClearValue(PlayerKey);
		}
		else 
		{
			Blackboard->SetValueAsObject(PlayerKey, Target);
		}
	}
}