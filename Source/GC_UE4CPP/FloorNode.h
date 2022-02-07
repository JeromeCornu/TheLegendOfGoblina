#pragma once

// Grid coordinates of the Upper left and Lower right node's corners
// Unreal convention is to put an F prefix for struct
struct FCornerCoordinates
{
	int32 UpperLeftX;
	int32 UpperLeftY;
	int32 LowerRightX;
	int32 LowerRightY;
};

class FloorNode
{
public:
	// Constructor
	FloorNode();
	FloorNode(const FCornerCoordinates& Coordinates);

	// Destructor:
	// (This class does not inherit from UE classes so we are responsible for its memory)
	~FloorNode();

	// Get/Set corner coordinates of the node
	// FORCEINLINE macro forces the compiler to copy paste function code on call instead of jumping into it.
	// This results in a speed up execution call but it takes more memory as it make the code bigger.
	FORCEINLINE FCornerCoordinates GetCornerCoordinates() const { return CornerCoordinates; }
	FORCEINLINE void SetCornerCoordinates(FCornerCoordinates Coordinates) { CornerCoordinates = Coordinates; }

	// Get the number of existing Nodes
	FORCEINLINE static int32 GetNodeCount() { return FloorNodeCount; }

private:
	FCornerCoordinates CornerCoordinates;

	// Count the number of existing Nodes. This ensures us that the memory is managed correctly
	static int32 FloorNodeCount;

};