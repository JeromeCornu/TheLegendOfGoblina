
#include "Components/StaticMeshComponent.h"
#include "PickableItem.h"

// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh Component as Root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Switch physics and collisions to false/true whenever this item gets picked/thrown
void APickableItem::TogglePhysicsAndCollision()
{
	StaticMesh->SetSimulatePhysics(!StaticMesh->IsSimulatingPhysics());
	SetActorEnableCollision(!GetActorEnableCollision());
}
