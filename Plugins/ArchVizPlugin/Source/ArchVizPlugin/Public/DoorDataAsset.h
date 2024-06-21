// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DoorDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FDoorTypee {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMesh* DoorMesh;
};

UCLASS()
class ARCHVIZPLUGIN_API UDoorDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TArray<FDoorTypee> DoorArray;
	
};
