// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"

#include "StandItem.generated.h"

class ABaseCharacter;
class ATargetPoint;
class APickableItem;

UCLASS()
class GC_UE4CPP_API AStandItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStandItem();


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
		FName SocketName;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<ATargetPoint> TargetPointClass;

	APickableItem* LaidItem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LayItem(APickableItem* item);

	void TakeItem(APickableItem* item);

	virtual void Interact(ABaseCharacter* character) override;
};
