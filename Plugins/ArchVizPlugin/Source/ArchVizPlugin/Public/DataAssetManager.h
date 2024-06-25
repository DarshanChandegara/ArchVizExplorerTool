// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAssetManager.generated.h"

USTRUCT(BlueprintType)
struct FDoorType {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
};

USTRUCT(BlueprintType)
struct FRoadMaterial {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* Material;
};

USTRUCT(BlueprintType)
struct FWallMaterial {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* Material;
};

USTRUCT(BlueprintType)
struct FChairType {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* ChairMesh;
};

USTRUCT(BlueprintType)
struct FStaticMeshtype {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;
};


UCLASS()
class ARCHVIZPLUGIN_API UDataAssetManager : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDoorType> DoorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoadMaterial> RoadMaterialArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWallMaterial> WallMaterialArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStaticMeshtype> ChairArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStaticMeshtype> TableArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStaticMeshtype> SofaArray;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStaticMeshtype> WallInteriorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStaticMeshtype> CeilInteriorArray;

	
};
