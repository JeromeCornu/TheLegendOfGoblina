// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralRoom.h"
#include "DrawDebugHelpers.h"
#include "FloorNode.h"
#include "Floor.h"

// Sets default values
AProceduralRoom::AProceduralRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorComponent"));
	SetRootComponent(FloorMesh);

	GridSizeX = 5;
	GridSizeY = 5;

	SquareWidth = 200.f;
	GridHeight = 1.f;
	RoomLength = 1000.f;
	RoomWidth = 1000.f;

	TopLeft = FVector(0.f);
	BottomRight = FVector(1000.f, 1000.f, 0.f);

	//Radius = 94;
	Radius = 65;
}

// Called when the game starts or when spawned
void AProceduralRoom::BeginPlay()
{
	Super::BeginPlay();

	TSharedPtr<Floor> TheFloor(new Floor());
	TheFloor->Partition();

	TheFloor->DrawFloorNodes(GetWorld());

	UE_LOG(LogTemp, Warning, TEXT("Number of nodes in partitioned floor stack: %d"), TheFloor->GetPartitionedFloor().Num());
	/*
	//SpawnItem(CrateClass);

	//CreateGrid();
	PlacePointsOnGrid();

	// To use our own custom class we need to use UE built-in pointer types (TUniquePtr or TSharedPtr)
	// so that we let UE delete this variable when it becomes unnecessary
	{
		UE_LOG(LogTemp, Warning, TEXT("Nodes in existence: %d"), FloorNode::GetNodeCount());
		TSharedPtr<FloorNode> NodePtr(new FloorNode());
		UE_LOG(LogTemp, Warning, TEXT("Nodes in existence: %d"), FloorNode::GetNodeCount());
	}
	UE_LOG(LogTemp, Warning, TEXT("Nodes in existence: %d"), FloorNode::GetNodeCount());
	*/
}

// Called every frame
void AProceduralRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralRoom::SpawnItem(UClass* ItemToSpawn)
{
	float XCoordinate = FMath::FRandRange(0.f, 1000.f);
	float YCoordinate = FMath::FRandRange(0.f, 1000.f);

	float Yaw = FMath::FRandRange(0.f, 360.f);

	FVector Location(XCoordinate, YCoordinate, 0.f);
	FRotator Rotation(0.f, Yaw, 0.f);

	GetWorld()->SpawnActor<AActor>(ItemToSpawn, Location, Rotation);
}


void AProceduralRoom::CreateGrid()
{
	for (int32 i = 0; i < GridSizeX + 1; i++)
	{
		FVector Start = TopLeft + FVector(i * SquareWidth, 0.f, GridHeight);
		FVector End = Start + FVector(0.f, RoomLength, 0.f);

		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, true);
	}

	for (int32 i = 0; i < GridSizeY + 1; i++)
	{
		FVector Start = TopLeft + FVector(0.f, i * SquareWidth, GridHeight);
		FVector End = Start + FVector(RoomWidth, 0.f, 0.f);

		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, true);
	}
}

FVector AProceduralRoom::GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight)
{
	float RandomX = FMath::FRandRange(UpperLeft.X, LowerRight.X);
	float RandomY = FMath::FRandRange(UpperLeft.Y, LowerRight.Y);

	return FVector(RandomX, RandomY, 0.f);
}

void AProceduralRoom::PlacePointsOnGrid()
{
	for (int32 i = 0; i < GridSizeX; i++)
	{
		for (int32 j = 0; j < GridSizeY; j++)
		{
			FVector UpperLeft(i * SquareWidth + Radius, j * SquareWidth + Radius, GridHeight);
			FVector LowerRight((i + 1) * SquareWidth - Radius, (j + 1) * SquareWidth - Radius, GridHeight);
			FVector RandomPointInSquare = GetRandomPointInSquare(UpperLeft, LowerRight);

			//DrawDebugPoint(GetWorld(), RandomPointInSquare, 5.f, FColor::Red, true);

			//DrawDebugCircle(GetWorld(), RandomPointInSquare, Radius, 48, FColor::Red, true, -1.f, 0, 5.f, FVector(0.f,1.f,0.f), FVector(1.f, 0.f, 0.f), true);
		
			//float RandomYaw = FMath::FRandRange(0.f, 360.f);
			float RandomYaw = 90.f * FMath::RandRange(0, 3);

			GetWorld()->SpawnActor<AActor>(CrateClass, RandomPointInSquare, FRotator(0.f, RandomYaw, 0.f));
		}
	}
}

