// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteriorGenerator.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API AInteriorGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteriorGenerator();

	UPROPERTY()
	USceneComponent* Scene;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Generate(UStaticMesh* StaticMesh);

};
