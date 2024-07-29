// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <ProceduralMeshComponent.h>
#include "ArchWizActor.h"
#include "WallGenerator.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API AWallGenerator : public AArchWizActor
{
	GENERATED_BODY()

	UPROPERTY()
	UStaticMeshComponent* WallSegment;

	UPROPERTY()
	int32 NoOfSegment = 0;

public:	

	UPROPERTY()
	USceneComponent* Scene;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMesh* WallMesh;

	TArray<UStaticMeshComponent*> WallArray;

protected:
	virtual void BeginPlay() override;

public:	
	AWallGenerator();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GenerateWall(int32 NoOfSegments);

	void ClearWalls();

	void HighlightWalls();
	void DeHighlightWalls();

	void HighlightWall();
	void DeHighlightWall();
	void SetMaterial(UMaterialInterface* Material);
	UMaterialInterface* GetMaterial(UStaticMeshComponent* MeshComponent);

	void SetWallSegment(UStaticMeshComponent* Segment);

	UStaticMeshComponent* GetWallSegment();

	void UpdateWallSegment(FVector Location, UStaticMesh* Mesh);

	void EndPlay(EEndPlayReason::Type Reason) override;

	void GenerateDoor(UStaticMesh* DoorMesh);

	void UpdateLocation();

	int32 GetNoOfSegment() { return NoOfSegment; }

	void SetNoOfSegment(int32 segmentNumber) {
		NoOfSegment = segmentNumber;
	}

};
