
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralRoom.generated.h"

UCLASS()
class PROSGENSERIES_API AProceduralRoom : public AActor
{
	GENERATED_BODY()
	
public:	

	AProceduralRoom();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FloorMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ChairClass;

	float SquareWidth;
	float GridHeight;
	float RoomLength;
	float RoomWidth;
	
	FVector TopLeft;
	FVector BottomRight;
	
	int32 GridSizeX;
	int32 GridSizeY;

	float Radius;
	
    void SpawnItem(UClass* ItemToSpawn, FVector SpawnLocation);

	void CreateGrid();

	FVector GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight);
	void PlacePointsOnGrid();
};
