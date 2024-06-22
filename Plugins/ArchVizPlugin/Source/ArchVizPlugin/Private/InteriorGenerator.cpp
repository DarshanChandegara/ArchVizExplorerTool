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
	MeshComponent = NewObject<UStaticMeshComponent>(this);
	MeshComponent->AttachToComponent(Scene, FAttachmentTransformRules::KeepRelativeTransform);
	MeshComponent->RegisterComponent();
	MeshComponent->SetStaticMesh(StaticMesh);
}

void AInteriorGenerator::SetStaticMesh(UStaticMesh* SMesh)
{
	if (MeshComponent) {
		MeshComponent->SetStaticMesh(SMesh);
	}
}

