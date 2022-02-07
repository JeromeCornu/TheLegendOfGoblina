// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"

#include "ObjectiveItem.generated.h"

class APickableItem;

UCLASS()
class GC_UE4CPP_API AObjectiveItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
		class AGC_UE4CPPGameModeBase* GameMode;
	
public:	
	// Sets default values for this actor's properties
	AObjectiveItem();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
		FName SocketName;

	UPROPERTY(EditAnywhere)
		int32 DestroyDelay;

	FTimerHandle TriggerDestroyTimerHandle;

	APickableItem* Item;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(ABaseCharacter* character) override;

	UFUNCTION()
		void TriggerDestroy();
};
