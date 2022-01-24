#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseCharacter.h"
#include "PickableItem.h"

// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh Component as Root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;

	// Create the Sphere trigger that signals to a character that he can grab this item
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();

	// Delegates
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APickableItem::CallbackComponentBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &APickableItem::CallbackComponentEndOverlap);
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

// Called when another actor enters the Sphere collider
void APickableItem::CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Press E to pick item"));
	
	// A Cast to ABaseCharacter is needed here
	ABaseCharacter* otherCharacter = (ABaseCharacter*)OtherActor;
	if (otherCharacter) 
	{
		otherCharacter->PickableItem = this;
	}
}

// Called when another actor exits the Sphere collider
void APickableItem::CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Cannot press E to pick item anymore"));

	// A Cast to ABaseCharacter is needed here
	ABaseCharacter* otherCharacter = (ABaseCharacter*)OtherActor;
	if (otherCharacter)
	{
		otherCharacter->PickableItem = nullptr;
	}
}

