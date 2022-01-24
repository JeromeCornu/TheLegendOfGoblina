// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"


// Detection + call functions when you've been see
AAIPatrol::AAIPatrol()
{
	// Initialize Senses
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

	// Collision Sphere's setup
	SphereRadius = 150.0f;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));
	MyCollisionSphere->InitSphereRadius(SphereRadius);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(RootComponent);

	// Connect the overlapping function to the sphere component 
	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAIPatrol::OnPlayerGrab);
}

void AAIPatrol::BeginPlay()
{
	Super::BeginPlay();

	// If player is caught, call the OnPlayerCaught function
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIPatrol::OnPlayerCaught);
	}
}

//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * !!! START DEBUG !!! * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void AAIPatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Purple, false, -1, 0, 1);
}
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * !!! END DEBUG !!! * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void AAIPatrol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Allow the AIPatrolController to possess the AIPatrol
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIPatrol::OnPlayerCaught(APawn* Pawn)
{
	// Get a reference to the player controller
	AAIPatrolController* AIController = Cast<AAIPatrolController>(GetController());

	// Cast succesful ?
	if (AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You have been see!"));
		// Call the function SetPlayerCaught in AIPatrolController
		AIController->SetPlayerCaught(Pawn);
	}
}

void AAIPatrol::OnPlayerGrab(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If the player has been grab -> play defeat
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Gotcha !"));
	}
}


