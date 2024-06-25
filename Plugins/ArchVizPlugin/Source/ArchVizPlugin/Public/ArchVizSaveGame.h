// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ArchVizSaveGame.generated.h"

USTRUCT()
struct FRoadActorProperty {

	GENERATED_BODY()

	UPROPERTY()
	FVector Dimenstion;

	UPROPERTY()
	FTransform RoadTransform;

	UPROPERTY()
	UMaterialInterface* Material;
};

USTRUCT()
struct FWallActorProperty {

	GENERATED_BODY()

	UPROPERTY()
	FTransform WallTransform;

	UPROPERTY()
	TArray<UStaticMesh*> WallWarray;

	UPROPERTY()
	UMaterialInterface* Material;

};

USTRUCT()
struct FInteriorActorProperty {
	GENERATED_BODY()

	UPROPERTY()
	FTransform ActorTransform;

	UPROPERTY()
	UStaticMesh* Mesh;
};

UCLASS()
class ARCHVIZPLUGIN_API UArchVizSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FRoadActorProperty> RoadActorArray;

	UPROPERTY()
	TArray<FWallActorProperty> WallActorArray;

	UPROPERTY()
	TArray<FInteriorActorProperty> InteriorActorArray;
	
};
