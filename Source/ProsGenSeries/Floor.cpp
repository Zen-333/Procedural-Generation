#include "Floor.h"

#include "FloorNode.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

Floor::Floor()
{
	FloorGridSizeX = 25;
	FloorGridSizeY = 25;
	RoomMinX = 1;
	RoomMinY = 1;

	UnitLength = 200.f;
	SplitChance = 3.5f;
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
		const int32 FloorLength = CornerCoordinates.LowerRightY - CornerCoordinates.UpperLeftY;
		float PercentageChanceOfSplit = (float)FloorLength / (float)FloorGridSizeY;
		PercentageChanceOfSplit *= SplitChance; // not needed, just to increase the chances of being split
		float DiceRoll = FMath::RandRange(0.f, 1.f);

		if (DiceRoll > PercentageChanceOfSplit)
		{
			return false;
		}
		if (FloorLength >= RoomMinY * 2)
		{
			return true;
		}
	}else if (Orientation == ESplitOrientation::ESO_Vertical)
	{
		const int32 FloorWidth = CornerCoordinates.LowerRightX - CornerCoordinates.UpperLeftX;
		float PercentageChanceOfSplit = (float)FloorWidth / (float)FloorGridSizeX;
		PercentageChanceOfSplit *= SplitChance; // not needed, just to increase the chances of being split
		float DiceRoll = FMath::RandRange(0.f, 1.f);

		if (DiceRoll > PercentageChanceOfSplit)
		{
			return false;
		}
		if (FloorWidth >= RoomMinX * 2)
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
		// try to split Horizontally
		if (ShouldSplitNode(InNode, ESplitOrientation::ESO_Horizontal))
		{
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitHorizontal(InNode, B, C);
			return true;
		}else if (ShouldSplitNode(InNode, ESplitOrientation::ESO_Vertical))
		{
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitVertical(InNode, B, C);
			return true;
		}
	}else if (HorizontalOrVertical == 1)
	{
		// Try to split Vertically
		if (ShouldSplitNode(InNode, ESplitOrientation::ESO_Vertical))
		{
			TSharedPtr<FloorNode> B(new FloorNode());
			TSharedPtr<FloorNode> C(new FloorNode());

			SplitVertical(InNode, B, C);
			return true;
		}else if (ShouldSplitNode(InNode, ESplitOrientation::ESO_Horizontal))
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
	const int32 SplitPointY = FMath::RandRange(InA->GetCornerCoordinates().UpperLeftY + RoomMinY, InA->GetCornerCoordinates().LowerRightY - RoomMinY);

	FCornerCoordinates CornerCoordinatesB;
	CornerCoordinatesB.UpperLeftX = InA->GetCornerCoordinates().UpperLeftX;
	CornerCoordinatesB.UpperLeftY = InA->GetCornerCoordinates().UpperLeftY;
	CornerCoordinatesB.LowerRightY = SplitPointY;
	CornerCoordinatesB.LowerRightX = InA->GetCornerCoordinates().LowerRightX;

	InB->SetCornerCoordinates(CornerCoordinatesB);
	FloorNodeStack.Push(InB);

	FCornerCoordinates CornerCoordinatesC;
	CornerCoordinatesC.LowerRightY = InA->GetCornerCoordinates().LowerRightY;
	CornerCoordinatesC.LowerRightX = InA->GetCornerCoordinates().LowerRightX;
	CornerCoordinatesC.UpperLeftX = InA->GetCornerCoordinates().UpperLeftX;
	CornerCoordinatesC.UpperLeftY = SplitPointY;

	InC->SetCornerCoordinates(CornerCoordinatesC);
	FloorNodeStack.Push(InC);
}

void Floor::SplitVertical(TSharedPtr<FloorNode> InA, TSharedPtr<FloorNode> InB, TSharedPtr<FloorNode> InC)
{
	const int32 SplitPointX = FMath::RandRange(InA->GetCornerCoordinates().UpperLeftX + RoomMinX, InA->GetCornerCoordinates().LowerRightX - RoomMinX);

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

void Floor::DrawFloorNodes(UWorld* World)
{
	for (int32 i = 0; i < PartitionedFloor.Num(); i++)
	{
		FCornerCoordinates Coordinates = PartitionedFloor[i]->GetCornerCoordinates();
		DrawFloorNode(World, Coordinates);
	}
}

void Floor::DrawFloorNode(UWorld* World, FCornerCoordinates Coordinates)
{
	const FVector UpperLeft(Coordinates.UpperLeftX * UnitLength, Coordinates.UpperLeftY * UnitLength, 2.0f);
	const FVector UpperRight(Coordinates.LowerRightX * UnitLength, Coordinates.UpperLeftY * UnitLength, 2.0f);
	const FVector LowerLeft(Coordinates.UpperLeftX * UnitLength, Coordinates.LowerRightY * UnitLength, 2.0f);
	const FVector LowerRight(Coordinates.LowerRightX * UnitLength, Coordinates.LowerRightY * UnitLength, 2.0f);
	
	DrawDebugLine(World, UpperLeft, UpperRight, FColor::Blue, true, -1, 0, 7.0f);
	DrawDebugLine(World, UpperLeft, LowerLeft, FColor::Blue, true, -1, 0, 7.0f);
	DrawDebugLine(World, LowerLeft, LowerRight, FColor::Blue, true, -1, 0, 7.0f);
	DrawDebugLine(World, UpperRight, LowerRight, FColor::Blue, true, -1, 0, 7.0f);
}
