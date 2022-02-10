// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "PlayableCharacter.h"
#include "PickableItem.h"
#include "GC_UE4CPPGameModeBase.h"
#include "Components/SphereComponent.h"
#include "BaseCharacter.h"

// Detection + call functions when you've been see
AAIPatrol::AAIPatrol()
{
	// Collision Sphere's setup
	SphereRadius = 150.0f;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));
	MyCollisionSphere->InitSphereRadius(SphereRadius);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(RootComponent);
	
	Spawner = nullptr;
}

void AAIPatrol::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());

	// Connect the overlapping function to the sphere component 
	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAIPatrol::OnPlayerCatch);
}

void AAIPatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIPatrol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Allow the AIPatrolController to possess the AIPatrol
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIPatrol::OnPlayerCatch(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Get a reference to the player
	APlayableCharacter* PlayerReference = Cast<APlayableCharacter>(OtherActor);

	// If the player has been grab -> play defeat
	if (PlayerReference)
	{
		GameMode->Lose();
		PlayerReference->PlayerEnd();
		AIEnd();
	}
}

void AAIPatrol::Despawn() 
{
	AController* AIController = GetController<AController>();
	
	float NumberAI = GameMode->GetAI();
	GameMode->SetAI(NumberAI - 1);

	if (AIController)
	{
		AIController->Destroy();
	}

	Destroy();
}

void AAIPatrol::AIEnd()
{
	//if the player fail the AI win
	ABaseCharacter::bDead = !GameMode->bVictory;

	AController* AIController = GetController<AController>();
	if (AIController)
	{
		AIController->Destroy();
	}
}


