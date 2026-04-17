#pragma once

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
	FloorNode();
	FloorNode(const FCornerCoordinates& Coordinates); // we pass it as a reference so we don't need to make any temporary copies
	~FloorNode();

	FORCEINLINE FCornerCoordinates GetCornerCoordinates() const {return CornerCoordinates;}
	FORCEINLINE void SetCornerCoordinates(const FCornerCoordinates Coordinates) {CornerCoordinates = Coordinates;}
	FORCEINLINE static int32 GetNodeCount() {return FloorNodeCount;}
	
private:
	FCornerCoordinates CornerCoordinates;

	static int32 FloorNodeCount;
};
