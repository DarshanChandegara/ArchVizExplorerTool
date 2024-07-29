// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ArchWizActor.h"
#include "RoofGenerator.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API ARoofGenerator : public AArchWizActor
{
	GENERATED_BODY()

	UPROPERTY()
	USceneComponent* Scene;
	
public:	

	UPROPERTY()
	UMaterialInterface* DefaultMaterial;

	UPROPERTY()
	UProceduralMeshComponent* Roof;

	UPROPERTY()
	UProceduralMeshComponent* Floor;

	UPROPERTY()
	FVector Dimention;

	UPROPERTY()
	FString Actortype;

	ARoofGenerator();

	UFUNCTION(BlueprintCallable)
	void GenerateRoof(FVector Dimensions, UMaterialInterface* Material , FVector offsets = FVector::ZeroVector);

	UFUNCTION(BlueprintCallable)
	void GenerateFloor(FVector Dimensions, UMaterialInterface* Material , FVector offsets = FVector::ZeroVector);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void HighlightRoof();

	void DeHighlightRoof();

	void SetMaterial(UMaterialInterface* Material);

	void UpdateLocation();

	void SetActorType(FString actor);

	FString GetActorType();

};
