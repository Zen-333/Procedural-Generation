
#include "ProceduralRoom.h"
#include "DrawDebugHelpers.h"
#include "Floor.h"


AProceduralRoom::AProceduralRoom()
{

	PrimaryActorTick.bCanEverTick = true;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	SetRootComponent(FloorMesh);

	GridSizeX = 5;
	GridSizeY = 5;
	SquareWidth = 200.f;
	GridHeight = 1.0f;
	RoomLength = 1000.0f;
	RoomWidth = 1000.0f;
	Radius = 25.f;

	TopLeft = FVector(0.f);
	BottomRight = FVector(1000.f, 1000.f, 0.f);
}

void AProceduralRoom::BeginPlay()
{
	Super::BeginPlay();

	TSharedPtr<Floor> TheFloor(new Floor());
	TheFloor->Partition();
	TheFloor->DrawFloorNodes(GetWorld());

	for (int i = 0; i < TheFloor->GetPartitionedFloor().Num(); i++)
	{
		float DiceRoll = FMath::RandRange(0, 1);
		if (DiceRoll < 0.5f)
		{
			float UpperLeftX = TheFloor->GetPartitionedFloor()[i]->GetCornerCoordinates().UpperLeftX * 200;
			float UpperLeftY = TheFloor->GetPartitionedFloor()[i]->GetCornerCoordinates().UpperLeftY * 200;

			float LowerRightX = TheFloor->GetPartitionedFloor()[i]->GetCornerCoordinates().LowerRightX * 200;
			float LowerRightY = TheFloor->GetPartitionedFloor()[i]->GetCornerCoordinates().LowerRightY * 200;
			FVector UpperLeft(UpperLeftX + 50, UpperLeftY + 50, 1.0f);
			FVector LowerRight(LowerRightX - 50, LowerRightY - 50, 1.0f);
			
			FVector RandomPoint = GetRandomPointInSquare(UpperLeft, LowerRight);
			UE_LOG(LogTemp, Warning, TEXT("RandomPoint: X: %f Y: %f Z: %f"), RandomPoint.X, RandomPoint.Y, RandomPoint.Z);
			SpawnItem(ChairClass, RandomPoint);
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Number of nodes in partitioned floor stack %d"),TheFloor->GetPartitionedFloor().Num());
	
	/* Unique ptr only allows one pointer to point to it at once shared ptr is the opposite allows multiple
	// unique ptr when the pointer goes out of scope (in this case once the begin play ends so the pointer life has ended) it destroyes the object
	//TUniquePtr<FloorNode> UniqueNodePtr(new FloorNode());
	{
		UE_LOG(LogTemp, Warning, TEXT("Nodes in existence: %d"), FloorNode::GetNodeCount());
		TSharedPtr<FloorNode> UniqueNodePtr(new FloorNode());
		UE_LOG(LogTemp, Warning, TEXT("Nodes in existence: %d"), FloorNode::GetNodeCount());
	}

	UE_LOG(LogTemp, Warning, TEXT("Nodes in existence: %d"), FloorNode::GetNodeCount());
	
	//FloorNode* Node = new FloorNode();
	
	//CreateGrid();
	//PlacePointsOnGrid();*/
	
}

void AProceduralRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralRoom::SpawnItem(UClass* ItemToSpawn, FVector SpawnLocation)
{
	//const float XCordinate = FMath::FRandRange(-50.f, 50.f);
	//const float YCordinate = FMath::FRandRange(-50.f, 50.f);

	const float Yaw = FMath::FRandRange(0.f, 360.f);

	//FVector Location(XCordinate, YCordinate, 0.f);
	FRotator Rotation(0.f, Yaw, 0.f);

	GetWorld()->SpawnActor<AActor>(ItemToSpawn, SpawnLocation, Rotation);
}

void AProceduralRoom::CreateGrid()
{
	for (int32 i = 0; i < GridSizeX + 1; i++)
	{
		FVector Start = TopLeft + FVector(i * SquareWidth, 0.f, GridHeight);
		FVector End = Start + FVector(0.f, RoomLength, GridHeight);
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, true);
	}

	for (int32 i = 0; i < GridSizeX + 1; i++)
	{
		FVector Start = TopLeft + FVector(0.f, i * SquareWidth, GridHeight);
		FVector End = Start + FVector(RoomLength, 0.f, GridHeight);
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
			FVector LowerRight(i * SquareWidth + SquareWidth - Radius, j * SquareWidth + SquareWidth - Radius, GridHeight);
			FVector RandomPointInSquare = GetRandomPointInSquare(UpperLeft, LowerRight);
			
			DrawDebugPoint(GetWorld(), RandomPointInSquare, 5.f, FColor::Red, true);

			const float Yaw = FMath::FRandRange(0.f, 360.f);
			GetWorld()->SpawnActor<AActor>(ChairClass, RandomPointInSquare, FRotator(0.f, Yaw, 0.f));
			DrawDebugCircle(GetWorld(), RandomPointInSquare, Radius, 40, FColor::Red, true, -1.f, 0, 2.5f, FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f), true);
		}
	}
}

