#include "Floor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

Floor::Floor()
{
	FloorGridSizeX = 8;
	FloorGridSizeY = 8;

	RoomMinX = 1;
	RoomMinY = 1;

	SplitChance = 1.25f;
}

Floor::Floor(int32 GridSizeX, int32 GridSizeY, int32 NodeMinX, int32 NodeMinY, float SplitChanceFactor)
{
	FloorGridSizeX = GridSizeX;
	FloorGridSizeY = GridSizeY;

	RoomMinX = NodeMinX;
	RoomMinY = NodeMinY;

	SplitChance = SplitChanceFactor;
}

Floor::~Floor()
{

}

void Floor::Partition()
{
	// Construct a Room sized FloorNode and push it into the stack to initialize the algorithm
	FCornerCoordinates CornerCoordinatesA = { 0, 0, FloorGridSizeX, FloorGridSizeY };
	FloorNodeStack.Push(TSharedPtr<FloorNode>(new FloorNode(CornerCoordinatesA)));

	while (FloorNodeStack.Num() > 0)
	{
		TSharedPtr<FloorNode> A = FloorNodeStack.Pop();

		bool bNodeWasSplit = SplitAttempt(A);
		if (!bNodeWasSplit)
		{
			PartitionedFloor.Push(A);
		}
	}
}

int32 Floor::CoinFlip()
{
	return FMath::RandRange(0, 1);
}

bool Floor::ShouldSplitNode(TSharedPtr<FloorNode> InNode, ESplitOrientation Orientation)
{
	FCornerCoordinates CornerCoordinates = InNode->GetCornerCoordinates();

	if (Orientation == ESplitOrientation::ESO_Horizontal)
	{
		int32 FloorLength = CornerCoordinates.LowerRightY - CornerCoordinates.UpperLeftY;
		float percentChanceOfSplit = SplitChance * (float)FloorLength / (float)FloorGridSizeY;
		float DiceRoll = FMath::FRandRange(0.f, 1.f);

		if (DiceRoll > percentChanceOfSplit)
		{
			return false;
		}

		if (FloorLength >= 2 * RoomMinY)
		{
			return true;
		}
	}
	else if(Orientation == ESplitOrientation::ESO_Vertical)
	{
		int32 FloorWidth = CornerCoordinates.LowerRightX - CornerCoordinates.UpperLeftX;
		float percentChanceOfSplit = SplitChance * (float)FloorWidth / (float)FloorGridSizeX;
		float DiceRoll = FMath::FRandRange(0.f, 1.f);

		if (DiceRoll > percentChanceOfSplit)
		{
			return false;
		}
		if (FloorWidth >= 2 * RoomMinX)
		{
			return true;
		}
	}

	return false;
}

bool Floor::SplitAttempt(TSharedPtr<FloorNode> InNode)
{
	int32 HorizontalOrVertical = CoinFlip();
	if (HorizontalOrVertical == 0)
	{
		if (ShouldSplitNode(InNode, ESplitOrientation::ESO_Horizontal))
		{
			//Try to split horizontally
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitHorizontal(InNode, B, C);
			return true;
		}
		else if (ShouldSplitNode(InNode, ESplitOrientation::ESO_Vertical)) 
		{
			//Try to split vertically
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitVertical(InNode, B, C);
			return true;
		}
	}
	else if(HorizontalOrVertical == 1)
	{
		if (ShouldSplitNode(InNode, ESplitOrientation::ESO_Vertical))
		{
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitVertical(InNode, B, C);
			return true;
		}
		else if (ShouldSplitNode(InNode, ESplitOrientation::ESO_Horizontal))
		{
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitHorizontal(InNode, B, C);
			return true;
		}
	}

	return false;
}

void Floor::SplitHorizontal(TSharedPtr<FloorNode> InA, TSharedPtr<FloorNode> InB, TSharedPtr<FloorNode> InC)
{
	int32 SplitPointY = FMath::RandRange(InA->GetCornerCoordinates().UpperLeftY + RoomMinY, InA->GetCornerCoordinates().LowerRightY - RoomMinY);

	FCornerCoordinates CornerCoordinatesB;
	CornerCoordinatesB.UpperLeftX = InA->GetCornerCoordinates().UpperLeftX;
	CornerCoordinatesB.UpperLeftY = InA->GetCornerCoordinates().UpperLeftY;
	CornerCoordinatesB.LowerRightX = InA->GetCornerCoordinates().LowerRightX;
	CornerCoordinatesB.LowerRightY = SplitPointY;

	InB->SetCornerCoordinates(CornerCoordinatesB);
	FloorNodeStack.Push(InB);

	FCornerCoordinates CornerCoordinatesC;
	CornerCoordinatesC.UpperLeftX = InA->GetCornerCoordinates().UpperLeftX;
	CornerCoordinatesC.UpperLeftY = SplitPointY;
	CornerCoordinatesC.LowerRightX = InA->GetCornerCoordinates().LowerRightX;
	CornerCoordinatesC.LowerRightY = InA->GetCornerCoordinates().LowerRightY;

	InC->SetCornerCoordinates(CornerCoordinatesC);
	FloorNodeStack.Push(InC);
}

void Floor::SplitVertical(TSharedPtr<FloorNode> InA, TSharedPtr<FloorNode> InB, TSharedPtr<FloorNode> InC)
{
	int32 SplitPointX = FMath::RandRange(InA->GetCornerCoordinates().UpperLeftX + RoomMinX, InA->GetCornerCoordinates().LowerRightX - RoomMinX);

	FCornerCoordinates CornerCoordinatesB;
	CornerCoordinatesB.UpperLeftX = InA->GetCornerCoordinates().UpperLeftX;
	CornerCoordinatesB.UpperLeftY = InA->GetCornerCoordinates().UpperLeftY;
	CornerCoordinatesB.LowerRightX = SplitPointX;
	CornerCoordinatesB.LowerRightY = InA->GetCornerCoordinates().LowerRightY;

	InB->SetCornerCoordinates(CornerCoordinatesB);
	FloorNodeStack.Push(InB);

	FCornerCoordinates CornerCoordinatesC;
	CornerCoordinatesC.UpperLeftX = SplitPointX;
	CornerCoordinatesC.UpperLeftY = InA->GetCornerCoordinates().UpperLeftY;
	CornerCoordinatesC.LowerRightX = InA->GetCornerCoordinates().LowerRightX;
	CornerCoordinatesC.LowerRightY = InA->GetCornerCoordinates().LowerRightY;

	InC->SetCornerCoordinates(CornerCoordinatesC);
	FloorNodeStack.Push(InC);
}

void Floor::DrawFloorNodes(UWorld* World, FVector Offset, float UnitLength, float GridHeight, float Thickness)
{
	for (int32 i = 0; i < PartitionedFloor.Num(); i++) 
	{
		FCornerCoordinates Coordinates = PartitionedFloor[i]->GetCornerCoordinates();
		DrawFloorNode(World, Coordinates, Offset, UnitLength, GridHeight, Thickness);
	}
}

void Floor::DrawFloorNode(UWorld* World, FCornerCoordinates coordinates, FVector Offset, float UnitLength, float GridHeight, float Thickness)
{
	FVector UpperLeft(coordinates.UpperLeftX * UnitLength, coordinates.UpperLeftY * UnitLength, GridHeight);
	FVector UpperRight(coordinates.LowerRightX * UnitLength, coordinates.UpperLeftY * UnitLength, GridHeight);
	FVector LowerLeft(coordinates.UpperLeftX * UnitLength, coordinates.LowerRightY * UnitLength, GridHeight);
	FVector LowerRight(coordinates.LowerRightX * UnitLength, coordinates.LowerRightY * UnitLength, GridHeight);

	UpperLeft += Offset;
	UpperRight += Offset;
	LowerLeft += Offset;
	LowerRight += Offset;

	DrawDebugLine(World, UpperLeft, UpperRight, FColor::Blue, true, -1, 0, Thickness);
	DrawDebugLine(World, UpperRight, LowerRight, FColor::Blue, true, -1, 0, Thickness);
	DrawDebugLine(World, LowerRight, LowerLeft, FColor::Blue, true, -1, 0, Thickness);
	DrawDebugLine(World, LowerLeft, UpperLeft, FColor::Blue, true, -1, 0, Thickness);
}