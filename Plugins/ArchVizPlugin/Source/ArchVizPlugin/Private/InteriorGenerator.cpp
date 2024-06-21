#include "InteriorGenerator.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "InteriorGenerator.h"

AInteriorGenerator::AInteriorGenerator()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

}

void AInteriorGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteriorGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteriorGenerator::Generate(UStaticMesh* StaticMesh)
{
	UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(this);
	Mesh->AttachToComponent(Scene, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->RegisterComponent();
	Mesh->SetStaticMesh(StaticMesh);
}

