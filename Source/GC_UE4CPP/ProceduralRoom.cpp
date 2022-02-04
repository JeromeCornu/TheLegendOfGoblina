// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralRoom.h"
#include "DrawDebugHelpers.h"
#include "Floor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"

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
	

	ObstacleWidth = 140.f;
	ObstaclesDensity = 0.4f;

	NodeWidth = 140.f;
	SplitFactor = 2.5f;

	RoomLength = 2000.f;
	RoomWidth = 2000.f;

	GridHeight = 5.f;

	FloorWidth = 200.f; 
	FloorHeight = 10.f;

	OffsetY = 0.f;
	WallHorizontalOffset = 80.f;
	WallHeight = 100.f;
}

// Called when the game starts or when spawned
void AProceduralRoom::BeginPlay()
{
	Super::BeginPlay();

	FloorRadius = FloorWidth / 2.f;
	NbFloorTilesX = (int32)(RoomLength / FloorWidth);
	NbFloorTilesY = (int32)(RoomWidth / FloorWidth);

	SafeZoneIndex = FMath::RandRange(0, NbFloorTilesY - 2);
	OffsetY = NodeWidth - (SafeZoneIndex + 1) * FloorWidth;
	UE_LOG(LogTemp, Warning, TEXT("**************************************** SafeZoneIndex: %d"), SafeZoneIndex);

	if (NodeWidth < ObstacleWidth) 
	{
		NodeWidth = ObstacleWidth;
	}

	ObstacleRadius = ObstacleWidth / 2.f;
	GridSizeX = (int32)((RoomLength - 2 * NodeWidth) / NodeWidth);
	GridSizeY = (int32)((RoomWidth - 2 * NodeWidth) / NodeWidth);

	Offset = FVector(NodeWidth, OffsetY, 0.f);

	BuildEmptyRoom();

	TSharedPtr<Floor> TheFloor(new Floor(GridSizeX, GridSizeY, 1, 1, SplitFactor));

	TheFloor->Partition();
	TheFloor->DrawFloorNodes(GetWorld(), Offset, NodeWidth, GridHeight, 4.f);

	SpawnItemsInGrid(TheFloor);
}

void AProceduralRoom::BuildEmptyRoom()
{
	FVector BuildOffset = FVector(-NodeWidth, -NodeWidth, 0.f) + Offset;

	for (int32 i = 0; i < NbFloorTilesX; i++)
	{
		for (int32 j = 0; j < NbFloorTilesY; j++)
		{
			FVector Location = BuildOffset + FVector(i * FloorWidth + FloorRadius, j * FloorWidth + FloorRadius, -FloorHeight);
			FloorHISMC->AddInstance(FTransform(Location));

			if (i == 0) 
			{
				if (j != SafeZoneIndex && j != SafeZoneIndex + 1) 
				{
					BuildWallOnFloor(Location, EWallOrientation::EWO_Left);
				}
			}
			else if (i == NbFloorTilesX - 1) 
			{
				BuildWallOnFloor(Location, EWallOrientation::EWO_Right);
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

FVector AProceduralRoom::GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight)
{
	float RandomX = FMath::FRandRange(UpperLeft.X, LowerRight.X);
	float RandomY = FMath::FRandRange(UpperLeft.Y, LowerRight.Y);

	return FVector(RandomX, RandomY, 0.f);
}

void AProceduralRoom::SpawnItemInNode(const FCornerCoordinates& Coordinates)
{
	FVector UpperLeft(Coordinates.UpperLeftX * NodeWidth + ObstacleRadius, Coordinates.UpperLeftY * NodeWidth + ObstacleRadius, 0.f);
	FVector LowerRight(Coordinates.LowerRightX * NodeWidth - ObstacleRadius, Coordinates.LowerRightY * NodeWidth - ObstacleRadius, 0.f);
	FVector RandomPointInSquare = GetRandomPointInSquare(UpperLeft, LowerRight);
	FVector Location = RandomPointInSquare + Offset;

	float RandomYaw = 90.f * FMath::RandRange(0, 3);
	FRotator Rotation(0.f, RandomYaw, 0.f);

	ObstaclesHISMC->AddInstance(FTransform(Rotation, Location));

	FVector UpperObstacleLocation = Location + FVector(0.f, 0.f, ObstacleWidth);
	float UpperObstacleRandomYaw = 90.f * FMath::RandRange(0, 3);
	FRotator UpperObstacleRotation(0.f, UpperObstacleRandomYaw, 0.f);

	ObstaclesHISMC->AddInstance(FTransform(UpperObstacleRotation, UpperObstacleLocation));
}

void AProceduralRoom::SpawnItemsInGrid(TSharedPtr<Floor> FloorGrid)
{
	TArray<TSharedPtr<FloorNode>> Partition = FloorGrid->GetPartitionedFloor();

	for (int32 i = 0; i < Partition.Num(); i++)
	{
		FCornerCoordinates Coordinates = Partition[i]->GetCornerCoordinates();

		float DiceRoll = FMath::FRandRange(0.f, 1.f);

		if (DiceRoll < ObstaclesDensity)
		{
			SpawnItemInNode(Coordinates);
		}
	}
}
