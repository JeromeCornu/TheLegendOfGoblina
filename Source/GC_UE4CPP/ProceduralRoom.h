// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorNode.h"

#include "ProceduralRoom.generated.h"

enum class EWallOrientation
{
	EWO_Upper,
	EWO_Lower,
	EWO_Right,
	EWO_Left
};

class Floor;
class UBoxComponent;

UCLASS()
class GC_UE4CPP_API AProceduralRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void BuildEmptyRoom();

	void BuildWallOnFloor(const FVector& FloorLocation, EWallOrientation Orientation);

	FVector GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight);

	void SpawnItemInNode(const FCornerCoordinates& Coordinates);

	void SpawnItemsInGrid(TSharedPtr<Floor> FloorGrid);
	
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* FloorHISMC;
	
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* ObstaclesHISMC;
	
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* WallsHISMC;
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> StandClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float FloorWidth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float FloorHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float ObstacleWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float ObstaclesDensity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float NodeWidth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float SplitFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float RoomLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float RoomWidth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float NumberOfStands;

	float FloorRadius;

	int32 NbFloorTilesX;
	int32 NbFloorTilesY;


	float ObstacleRadius;

	int32 GridSizeX;
	int32 GridSizeY;

	// Draw helpers grid height
	float GridHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float OffsetY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float WallHeight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		float WallHorizontalOffset;

	int32 SafeZoneIndex;

	FVector Offset;

};
