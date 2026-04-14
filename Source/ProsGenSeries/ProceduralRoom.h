
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
	UStaticMeshComponent* Floor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ChairClass;

    void SpawnItem(UClass* ItemToSpawn);
};
