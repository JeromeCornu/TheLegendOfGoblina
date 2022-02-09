// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralRoom.h"
#include "DrawDebugHelpers.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Floor.h"
#include "StandItem.h"
#include "PickableItem.h"

// Sets default values
AProceduralRoom::AProceduralRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FloorHISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Floor HISMC"));
	SetRootComponent(FloorHISMC);
	FloorHISMC->SetMobility(EComponentMobility::Static);

	ObstaclesHISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Obstacles HISMC"));
	ObstaclesHISMC->SetupAttachment(RootComponent);
	ObstaclesHISMC->SetMobility(EComponentMobility::Static);
	
	WallsHISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Walls HISMC"));
	WallsHISMC->SetupAttachment(RootComponent);
	WallsHISMC->SetMobility(EComponentMobility::Static);
	

	RoomTargetLength = 2000.f;
	RoomTargetWidth = 2000.f;
	CorridorsTargetWidth = 200.f;
	UnitNodeWidth = 140.f;
	SplitFactor = 2.5f;
	ObstaclesDensity = 0.4f;
	NumberOfStands = 10;
	NbFoodToSpawn = 1;
	SafeZoneAccessSize = 2;
	PatrolSpawnSize = 3;
	bDrawDebugGrid = false;
	DebugGridHeight = 5.f;

	FloorWidth = 200.f; 
	FloorHeight = 10.f;
	ObstacleWidth = 140.f;
	ObstacleHeight = 130.f;
	WallHorizontalOffset = 80.f;
	WallHeight = 100.f;
}

// Called when the game starts or when spawned
void AProceduralRoom::BeginPlay()
{
	Super::BeginPlay();

	SetupLayOutParameters();

	BuildEmptyRoom();

	FillProceduralRoom();
}

void AProceduralRoom::SetupLayOutParameters() 
{
	if (UnitNodeWidth < ObstacleWidth) 
	{
		UnitNodeWidth = ObstacleWidth;
	}

	NbFloorTilesX = (int32)(RoomTargetLength / FloorWidth);
	NbFloorTilesY = (int32)(RoomTargetWidth / FloorWidth);

	float RoomRealLength = NbFloorTilesX * FloorWidth;
	float RoomRealWidth = NbFloorTilesY * FloorWidth;

	GridSizeX = (int32)((RoomRealLength - 2 * CorridorsTargetWidth) / UnitNodeWidth);
	GridSizeY = (int32)((RoomRealWidth - 2 * CorridorsTargetWidth) / UnitNodeWidth);

	CorridorsWidthX = (RoomRealLength - GridSizeX * UnitNodeWidth) / 2.f;
	CorridorsWidthY = (RoomRealWidth - GridSizeY * UnitNodeWidth) / 2.f;

	SafeZoneIndex = FMath::RandRange(0, NbFloorTilesY - SafeZoneAccessSize);
	float OffsetY = CorridorsWidthY - (SafeZoneIndex + 1) * FloorWidth;
	RoomOffset = FVector(CorridorsWidthX, OffsetY, 0.f);

	PatrolSpawnIndex = FMath::RandRange(0, NbFloorTilesY - PatrolSpawnSize);
}

void AProceduralRoom::BuildEmptyRoom()
{
	FVector FloorMeshOffset(FloorWidth / 2.f, FloorWidth / 2.f, -FloorHeight);
	FVector CorridorsOffset(CorridorsWidthX, CorridorsWidthY, 0.f);
	FVector BuildOffset = RoomOffset + FloorMeshOffset - CorridorsOffset;

	for (int32 i = 0; i < NbFloorTilesX; i++)
	{
		for (int32 j = 0; j < NbFloorTilesY; j++)
		{
			FVector Location = BuildOffset + FVector(i * FloorWidth, j * FloorWidth, 0.f);
			FloorHISMC->AddInstance(FTransform(Location));

			if (i == 0) 
			{
				if (j < SafeZoneIndex || j >= SafeZoneIndex + SafeZoneAccessSize)
				{
					BuildWallOnFloor(Location, EWallOrientation::EWO_Left);
				}
			}
			else if (i == NbFloorTilesX - 1) 
			{
				if (j < PatrolSpawnIndex || j >= PatrolSpawnIndex + PatrolSpawnSize)
				{
					BuildWallOnFloor(Location, EWallOrientation::EWO_Right);
				}
			}

			if (j == 0)
			{
				BuildWallOnFloor(Location, EWallOrientation::EWO_Upper);
			}
			else if (j == NbFloorTilesY - 1)
			{
				BuildWallOnFloor(Location, EWallOrientation::EWO_Lower);
			}
		}
	}

	BuildPatrolSpawn(BuildOffset);
}

void AProceduralRoom::BuildWallOnFloor(const FVector& FloorLocation, EWallOrientation Orientation)
{
	FRotator WallRotation = FRotator::ZeroRotator;
	FVector WallLocation = FloorLocation + FVector(0.f, 0.f, WallHeight + FloorHeight);

	if (Orientation == EWallOrientation::EWO_Left)
	{
		WallRotation.Yaw = 90.f;
		WallLocation.X -= WallHorizontalOffset;
	}
	else if (Orientation == EWallOrientation::EWO_Right)
	{
		WallRotation.Yaw = 90.f;
		WallLocation.X += WallHorizontalOffset;
	}
	else if (Orientation == EWallOrientation::EWO_Upper)
	{
		WallRotation.Yaw = 0.f;
		WallLocation.Y -= WallHorizontalOffset;
	}
	else if (Orientation == EWallOrientation::EWO_Lower)
	{
		WallRotation.Yaw = 0.f;
		WallLocation.Y += WallHorizontalOffset;
	}

	FVector UpperWallLocation = WallLocation + FVector(0.f, 0.f, 2 * WallHeight);

	WallsHISMC->AddInstance(FTransform(WallRotation, WallLocation));
	WallsHISMC->AddInstance(FTransform(WallRotation, UpperWallLocation));
}

void AProceduralRoom::BuildPatrolSpawn(const FVector& BuildOffset)
{
	FRotator Rotation(0.f, 90.f, 0.f);
	FVector Location = BuildOffset;

	Location.X += (NbFloorTilesX - 1) * FloorWidth + DoorHorizontalOffset;
	Location.Y += (PatrolSpawnIndex + (PatrolSpawnSize - 1) / 2.f) * FloorWidth;
	Location.Z += DoorHeight;

	GetWorld()->SpawnActor<AActor>(PatrolSpawnerClass, Location, Rotation);
}

void AProceduralRoom::FillProceduralRoom()
{
	TSharedPtr<Floor> TheFloor(new Floor(GridSizeX, GridSizeY, 1, 1, SplitFactor));

	TheFloor->Partition();

	TArray<TSharedPtr<FloorNode>> Partition = TheFloor->GetPartitionedFloor();

	if (bDrawDebugGrid)
	{
		TheFloor->DrawFloorNodes(GetWorld(), RoomOffset, UnitNodeWidth, DebugGridHeight, 4.f);
	}

	SpawnStandsInPartition(Partition);

	SpawnObstaclesInPartition(Partition);
}

void AProceduralRoom::SpawnStandsInPartition(TArray<TSharedPtr<FloorNode>>& Partition)
{
	for (int32 i = 0; i < NumberOfStands; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, Partition.Num() - 1);

		FCornerCoordinates Coordinates = Partition[RandomIndex]->GetCornerCoordinates();

		if (i < NbFoodToSpawn)
		{
			SpawnObstacleInNode(Coordinates, EObjectOnObstacle::EOOO_StandWithFood);
		}
		else
		{
			SpawnObstacleInNode(Coordinates, EObjectOnObstacle::EOOO_Stand);
		}

		Partition.RemoveAt(RandomIndex);
	}
}

void AProceduralRoom::SpawnObstacleInNode(const FCornerCoordinates& Coordinates, EObjectOnObstacle ObjectOnObstacle)
{
	FVector CollisionAvoidanceMargin(ObstacleWidth / 2.f, ObstacleWidth / 2.f, 0.f);
	FVector UpperLeft = FVector(Coordinates.UpperLeftX * UnitNodeWidth, Coordinates.UpperLeftY * UnitNodeWidth, 0.f) + CollisionAvoidanceMargin;
	FVector LowerRight = FVector(Coordinates.LowerRightX * UnitNodeWidth, Coordinates.LowerRightY * UnitNodeWidth, 0.f) - CollisionAvoidanceMargin;
	FVector RandomPointInSquare = GetRandomPointInSquare(UpperLeft, LowerRight);
	
	FVector Location = RandomPointInSquare + RoomOffset;
	AddObstacleInstanceAtLocation(Location);

	if (ObjectOnObstacle != EObjectOnObstacle::EOOO_Empty)
	{
		FVector UpperLocation = Location + FVector(0.f, 0.f, ObstacleHeight);

		if (ObjectOnObstacle == EObjectOnObstacle::EOOO_Obstacle)
		{
			AddObstacleInstanceAtLocation(UpperLocation);
		}
		else if (ObjectOnObstacle == EObjectOnObstacle::EOOO_Stand)
		{
			GetWorld()->SpawnActor<AStandItem>(StandClass, UpperLocation, FRotator::ZeroRotator);
		}
		else if (ObjectOnObstacle == EObjectOnObstacle::EOOO_StandWithFood)
		{
			SpawnStandWithFoodAtLocation(UpperLocation);
		}
	}
}

FVector AProceduralRoom::GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight)
{
	float RandomX = FMath::FRandRange(UpperLeft.X, LowerRight.X);
	float RandomY = FMath::FRandRange(UpperLeft.Y, LowerRight.Y);

	return FVector(RandomX, RandomY, 0.f);
}

void AProceduralRoom::AddObstacleInstanceAtLocation(const FVector& Location) 
{
	float RandomYaw = 90.f * FMath::RandRange(0, 3);
	FRotator Rotation(0.f, RandomYaw, 0.f);
	ObstaclesHISMC->AddInstance(FTransform(Rotation, Location));
}

void AProceduralRoom::SpawnStandWithFoodAtLocation(const FVector& Location)
{
	AStandItem* Plate = GetWorld()->SpawnActor<AStandItem>(StandClass, Location, FRotator::ZeroRotator);
	UStaticMeshComponent* Mesh = Plate->StaticMesh;
	FName Socket = Plate->SocketName;

	FVector FoodLocation = Mesh->GetSocketLocation(Socket);
	FRotator FoodRotation = Mesh->GetSocketRotation(Socket);

	APickableItem* Food = GetWorld()->SpawnActor<APickableItem>(FoodClass, FoodLocation, FoodRotation);
	Food->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);

	Plate->LaidItem = Food;
}

void AProceduralRoom::SpawnObstaclesInPartition(const TArray<TSharedPtr<FloorNode>>& Partition)
{
	for (int32 i = 0; i < Partition.Num(); i++)
	{
		FCornerCoordinates Coordinates = Partition[i]->GetCornerCoordinates();

		float DiceRoll = FMath::FRandRange(0.f, 1.f);

		if (DiceRoll < ObstaclesDensity)
		{
			SpawnObstacleInNode(Coordinates, EObjectOnObstacle::EOOO_Obstacle);
		}
	}
}