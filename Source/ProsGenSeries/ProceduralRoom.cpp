
#include "ProceduralRoom.h"
#include "Kismet/KismetMathLibrary.h"


AProceduralRoom::AProceduralRoom()
{

	PrimaryActorTick.bCanEverTick = true;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorComponent"));

	SetRootComponent(Floor);
}

void AProceduralRoom::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnItem(ChairClass);
	SpawnItem(ChairClass);
	SpawnItem(ChairClass);
	SpawnItem(ChairClass);
}

void AProceduralRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralRoom::SpawnItem(UClass* ItemToSpawn)
{
	const float XCordinate = FMath::FRandRange(-50.f, 50.f);
	const float YCordinate = FMath::FRandRange(-50.f, 50.f);

	const float Yaw = FMath::FRandRange(0.f, 360.f);

	FVector Location(XCordinate, YCordinate, 0.f);
	FRotator Rotation(0.f, Yaw, 0.f);

	GetWorld()->SpawnActor<AActor>(ItemToSpawn, Location, Rotation);
}

