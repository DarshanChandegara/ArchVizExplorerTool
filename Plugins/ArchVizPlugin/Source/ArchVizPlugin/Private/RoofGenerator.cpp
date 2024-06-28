// Fill out your copyright notice in the Description page of Project Settings.


#include "RoofGenerator.h"

ARoofGenerator::ARoofGenerator()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Roof = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Roof"));
	Roof->SetupAttachment(Scene);

	Floor = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Floor"));
	Floor->SetupAttachment(Scene);

}

void ARoofGenerator::GenerateRoof(FVector Dimensions, UMaterialInterface* Material, FVector Offset)
{
	Roof->ClearAllMeshSections();
	Floor->ClearAllMeshSections();

	Dimention = Dimensions;
	Actortype = "Roof";
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;


	//Front
	Vertices.Add(FVector(0, Dimensions.Y, 0) + Offset);
	Vertices.Add(FVector(0, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, 0) + Offset);

	//Back
	Vertices.Add(FVector(0, 0, 0) + Offset);
	Vertices.Add(FVector(0, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, 0) + Offset);


	//Left
	Vertices.Add(FVector(0, 0, 0) + Offset);
	Vertices.Add(FVector(0, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(0, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(0, Dimensions.Y, 0) + Offset);

	//Right
	Vertices.Add(FVector(Dimensions.X, 0, 0) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, 0) + Offset);

	//Top
	Vertices.Add(FVector(0, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(0, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, Dimensions.Z) + Offset);

	//Bottom
	Vertices.Add(FVector(0, Dimensions.Y, 0) + Offset);
	Vertices.Add(FVector(0, 0, 0) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, 0) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, 0) + Offset);


	// triangles (two triangles per face)
	Triangles.Append({
		0, 3, 1, 1, 3, 2,
		4, 5, 7, 5, 6, 7,
		8, 11, 9, 9, 11, 10,
		12, 13, 15, 13, 14, 15,
		16, 19, 17, 17, 19, 18,
		20, 21, 23, 21, 22, 23
		});

	// normals (perpendicular to each face)

	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(0, 1, 0));
	}
	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(0, -1, 0));
	}
	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(-1, 0, 0));
	}
	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(1, 0, 0));
	}
	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, 1));
	}

	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, -1));
	}


	//UV Mapping
	for (int32 i{}; i < 3; ++i)
	{
		UVs.Add(FVector2D(0, 1));
		UVs.Add(FVector2D(0, 0));
		UVs.Add(FVector2D(1, 0));
		UVs.Add(FVector2D(1, 1));

		UVs.Add(FVector2D(0, 1));
		UVs.Add(FVector2D(0, 0));
		UVs.Add(FVector2D(-1, 0));
		UVs.Add(FVector2D(-1, 1));
	}


	Roof->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);

	Roof->SetMaterial(0, Material);
}

void ARoofGenerator::GenerateFloor(FVector Dimensions, UMaterialInterface* Material, FVector Offset)
{
	Roof->ClearAllMeshSections();
	Floor->ClearAllMeshSections();

	Dimention = Dimensions;
	Actortype = "Floor";


	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;


	//Front
	Vertices.Add(FVector(0, Dimensions.Y, 0) + Offset);
	Vertices.Add(FVector(0, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, 0) + Offset);

	//Back
	Vertices.Add(FVector(0, 0, 0) + Offset);
	Vertices.Add(FVector(0, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, 0) + Offset);


	//Left
	Vertices.Add(FVector(0, 0, 0) + Offset);
	Vertices.Add(FVector(0, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(0, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(0, Dimensions.Y, 0) + Offset);

	//Right
	Vertices.Add(FVector(Dimensions.X, 0, 0) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, 0) + Offset);

	//Top
	Vertices.Add(FVector(0, Dimensions.Y, Dimensions.Z) + Offset);
	Vertices.Add(FVector(0, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, Dimensions.Z) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, Dimensions.Z) + Offset);

	//Bottom
	Vertices.Add(FVector(0, Dimensions.Y, 0) + Offset);
	Vertices.Add(FVector(0, 0, 0) + Offset);
	Vertices.Add(FVector(Dimensions.X, 0, 0) + Offset);
	Vertices.Add(FVector(Dimensions.X, Dimensions.Y, 0) + Offset);


	// triangles (two triangles per face)
	Triangles.Append({
		0, 3, 1, 1, 3, 2,
		4, 5, 7, 5, 6, 7,
		8, 11, 9, 9, 11, 10,
		12, 13, 15, 13, 14, 15,
		16, 19, 17, 17, 19, 18,
		20, 21, 23, 21, 22, 23
		});

	// normals (perpendicular to each face)

	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(0, 1, 0));
	}
	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(0, -1, 0));
	}
	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(-1, 0, 0));
	}
	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(1, 0, 0));
	}
	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, 1));
	}

	for (int32 i{}; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, -1));
	}


	//UV Mapping
	for (int32 i{}; i < 3; ++i)
	{
		UVs.Add(FVector2D(0, 1));
		UVs.Add(FVector2D(0, 0));
		UVs.Add(FVector2D(1, 0));
		UVs.Add(FVector2D(1, 1));

		UVs.Add(FVector2D(0, 1));
		UVs.Add(FVector2D(0, 0));
		UVs.Add(FVector2D(-1, 0));
		UVs.Add(FVector2D(-1, 1));
	}


	Floor->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
	Floor->SetMaterial(0, Material);
}

void ARoofGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoofGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoofGenerator::HighlightRoof()
{
	Roof->SetRenderCustomDepth(true);
	Roof->CustomDepthStencilValue = 2.0;

	Floor->SetRenderCustomDepth(true);
	Floor->CustomDepthStencilValue = 2.0;

	
}

void ARoofGenerator::DeHighlightRoof()
{
	Roof->SetRenderCustomDepth(false);
	Floor->SetRenderCustomDepth(false);
}

void ARoofGenerator::SetMaterial(UMaterialInterface* Material)
{
	DefaultMaterial = Material;
	UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(Material, this);

	float TileX = Dimention.X / 150.f;
	float TileY = Dimention.Y / 150.f;

	MaterialInstance->SetScalarParameterValue(TEXT("TileX"), TileX);
	MaterialInstance->SetScalarParameterValue(TEXT("TileY"), TileY);
	Roof->SetMaterial(0, MaterialInstance);
	Floor->SetMaterial(0, MaterialInstance);
}

void ARoofGenerator::UpdateLocation()
{
	if (FVector StartLocation_, WorldDirection;Controller-> DeprojectMousePositionToWorld(StartLocation_, WorldDirection))
	{
		FVector EndLocation_ = StartLocation_ + WorldDirection * 100000;

		FCollisionQueryParams Params;
		Params.bTraceComplex = true;
		Params.AddIgnoredActor(this);

		if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation_, EndLocation_,
			ECC_Visibility, Params))
		{
			FVector Location = HitResult.Location;
			//Location.Z += WallWidget->ZOffset->GetValue();
			SetActorLocation(Location);

			SnapActor(this, 20);
		}
	}
}

