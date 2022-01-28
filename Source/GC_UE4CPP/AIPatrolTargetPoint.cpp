// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrolTargetPoint.h"
#include "Components/SphereComponent.h"


AAIPatrolTargetPoint::AAIPatrolTargetPoint()
{
	// Collision Sphere's setup
	SphereRadius = 150.0f;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));
	MyCollisionSphere->InitSphereRadius(SphereRadius);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(RootComponent);

	// Connect the overlapping function to the sphere component 
	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAIPatrolTargetPoint::OnSteakClose);
}

void AAIPatrolTargetPoint::OnSteakClose(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Get a reference to the Aliment
	// ASteak* SteakReference = (ASteak*)OtherActor;

	// Get the position and rotation of the plate
	NewRotation = this->GetActorRotation();
	NewLocation = this->GetActorLocation();

	// If the aliment is close -> teleport it on the plate
	if ((OtherActor != nullptr) && (OtherActor->ActorHasTag(TEXT("Food"))) //  && (Food != attrapé)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Steak found !"));
		SetActorLocationAndRotation(NewLocation, NewRotation, false, 0, ETeleportType::None);
	}
}
