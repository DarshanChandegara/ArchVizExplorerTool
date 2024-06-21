// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <ProceduralMeshComponent.h>
#include "WallGenerator.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API AWallGenerator : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	USceneComponent* Scene;

	UPROPERTY()
	UStaticMeshComponent* WallSegment;

	TArray<UStaticMeshComponent*> WallArray;
	
public:	

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMesh* WallMesh;

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

	void SetWallSegment(UStaticMeshComponent* Segment);
	UStaticMeshComponent* GetWallSegment();

};
