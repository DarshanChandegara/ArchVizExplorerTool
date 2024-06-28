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

void AInteriorGenerator::HighlightInterior()
{
	MeshComponent->SetRenderCustomDepth(true);
	MeshComponent->CustomDepthStencilValue = 2.0;
}

void AInteriorGenerator::DeHighlightInterior()
{
	MeshComponent->SetRenderCustomDepth(false);
}

void AInteriorGenerator::UpdateLocation()
{
	if (FVector StartLocation_, WorldDirection; Controller-> DeprojectMousePositionToWorld(StartLocation_, WorldDirection))
	{
		FVector EndLocation_ = StartLocation_ + WorldDirection * 100000;

		FCollisionQueryParams Params;
		Params.bTraceComplex = true;
		Params.AddIgnoredActor(this);

		if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation_, EndLocation_,
			ECC_Visibility, Params))
		{
			FVector Location = HitResult.Location;
			SetActorLocation(Location);
		}
	}
}

