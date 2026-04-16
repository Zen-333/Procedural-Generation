#include "FloorNode.h"

FloorNode::FloorNode()
{
	UE_LOG(LogTemp, Warning, TEXT("FloorNode Created"));
}

FloorNode::FloorNode(const FCornerCoordinates& Coordinates)
{
	CornerCoordinates.UpperLeftX = Coordinates.UpperLeftX;
	CornerCoordinates.UpperLeftY = Coordinates.UpperLeftY;
	CornerCoordinates.LowerRightX = Coordinates.LowerRightX;
	CornerCoordinates.LowerRightY = Coordinates.LowerRightY;

	UE_LOG(LogTemp, Warning, TEXT("FloorNode Created"));
}

FloorNode::~FloorNode()
{
	UE_LOG(LogTemp, Warning, TEXT("FloorNode Destroyed"));
}
