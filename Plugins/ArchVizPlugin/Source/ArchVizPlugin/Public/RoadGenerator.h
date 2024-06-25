#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <ProceduralMeshComponent.h>
#include "RoadGenerator.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API ARoadGenerator : public AActor
{
	GENERATED_BODY()

public:
	ARoadGenerator();

	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent* Road;

	UPROPERTY()
	FVector Size;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GenerateRoad(FVector Dimenstion, FVector Offset, UMaterialInterface* Material);

	void HighlightRoad();
	void DeHighlightRoad();
	void SetMaterial(UMaterialInterface* Material);

};
