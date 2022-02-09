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

enum class EObjectOnObstacle
{
	EOOO_Empty,
	EOOO_Obstacle,
	EOOO_Stand,
	EOOO_StandWithFood
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

	void SetupLayOutParameters();

	void BuildEmptyRoom();

	void BuildWallOnFloor(const FVector& FloorLocation, EWallOrientation Orientation);

	void BuildPatrolSpawn(const FVector& BuildOffset);

	void FillProceduralRoom();

	void SpawnStandsInPartition(TArray<TSharedPtr<FloorNode>>& Partition);

	void SpawnObstacleInNode(const FCornerCoordinates& Coordinates, EObjectOnObstacle ObjectOnObstacle);

	FVector GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight);

	void AddObstacleInstanceAtLocation(const FVector& Location);

	void SpawnStandWithFoodAtLocation(const FVector& Location);

	void SpawnObstaclesInPartition(const TArray<TSharedPtr<FloorNode>>& Partition);

	
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* FloorHISMC;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* ObstaclesHISMC;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* WallsHISMC;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		float RoomTargetLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		float RoomTargetWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		float CorridorsTargetWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		float UnitNodeWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		float SplitFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		float ObstaclesDensity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		int32 NumberOfStands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> StandClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		int32 NbFoodToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> FoodClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> PatrolSpawnerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		int32 SafeZoneAccessSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		int32 PatrolSpawnSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		bool bDrawDebugGrid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Room Parameters", meta = (AllowPrivateAccess = "true"))
		float DebugGridHeight;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Meshes Dimensions | Floor Mesh", meta = (AllowPrivateAccess = "true"))
		float FloorWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Meshes Dimensions | Floor Mesh", meta = (AllowPrivateAccess = "true"))
		float FloorHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Meshes Dimensions | Obstacle Mesh", meta = (AllowPrivateAccess = "true"))
		float ObstacleWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Meshes Dimensions | Obstacle Mesh", meta = (AllowPrivateAccess = "true"))
		float ObstacleHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Meshes Dimensions | Wall Mesh", meta = (AllowPrivateAccess = "true"))
		float WallHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Meshes Dimensions | Wall Mesh", meta = (AllowPrivateAccess = "true"))
		float WallHorizontalOffset;


	int32 NbFloorTilesX;
	int32 NbFloorTilesY;

	int32 SafeZoneIndex;
	int32 PatrolSpawnIndex;

	float CorridorsWidthX;
	float CorridorsWidthY;

	FVector RoomOffset;

	int32 GridSizeX;
	int32 GridSizeY;
};
