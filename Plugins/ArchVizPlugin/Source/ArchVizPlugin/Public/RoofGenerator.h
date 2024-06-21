// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "RoofGenerator.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API ARoofGenerator : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	UProceduralMeshComponent* Roof;
	
public:	
	ARoofGenerator();

	UFUNCTION(BlueprintCallable)
	void GenerateRoof(FVector Dimensions, UMaterialInterface* Material , FVector Offset = FVector::ZeroVector);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void HighlightRoof();

	void DeHighlightRoof();

};
