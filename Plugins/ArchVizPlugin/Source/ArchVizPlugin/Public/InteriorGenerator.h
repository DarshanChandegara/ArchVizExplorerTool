// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArchWizActor.h"
#include "InteriorGenerator.generated.h"

UENUM()
enum class EInteriorAttchmentType : int8 {
	AnyWhere ,
	Floor , 
	Ceil ,
	Wall
};

UCLASS()
class ARCHVIZPLUGIN_API AInteriorGenerator : public AArchWizActor
{
	GENERATED_BODY()

public:	
	AInteriorGenerator();

	UPROPERTY()
	USceneComponent* Scene;

	UPROPERTY()
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	TEnumAsByte<EInteriorAttchmentType> InteriorAttchmentType;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Generate(UStaticMesh* StaticMesh);

	void SetStaticMesh(UStaticMesh* SMesh);

	void HighlightInterior();

	void DeHighlightInterior();

	void UpdateLocation();

};
