#include "Floor.h"

#include "FloorNode.h"

Floor::Floor()
{
	FloorGridSizeX = 5;
	FloorGridSizeY = 5;
	RoomMinX = 1;
	RoomMinY = 1;
}

Floor::~Floor()
{
}

void Floor::Partition()
{
	FCornerCoordinates CornerCoordinatesA = {0, 0, FloorGridSizeX, FloorGridSizeY};
	FloorNodeStack.Push(TSharedPtr<FloorNode>(new FloorNode(CornerCoordinatesA))); // creating a variable without giving it a name

	while (FloorNodeStack.Num() > 0)
	{
		TSharedPtr<FloorNode> A = FloorNodeStack.Pop(); // it pops the variable and store it in A

		UE_LOG(LogTemp, Warning, TEXT("Popping a FloorNode off the stack"));
	}
}

int32 Floor::CoinFlip()
{
	return 0;
}

bool Floor::ShouldSplitNode(TSharedPtr<FloorNode> InNode, ESplitOrientation Orientation)
{
	return false;
}

bool Floor::SplitAttempt(TSharedPtr<FloorNode> InNode)
{
	return false;
}

void Floor::SplitHorizontal(TSharedPtr<FloorNode> InA, TSharedPtr<FloorNode> InB, TSharedPtr<FloorNode> InC)
{
	
}

void Floor::SplitVertical(TSharedPtr<FloorNode> InA, TSharedPtr<FloorNode> InB, TSharedPtr<FloorNode> InC)
{
	
}
