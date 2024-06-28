// Fill out your copyright notice in the Description page of Project Settings.


#include "WallGenerator.h"

AWallGenerator::AWallGenerator()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
}

void AWallGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWallGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallGenerator::GenerateWall(int32 NoOfSegments)
{
	ClearWalls();

	for (int32 i = 0; i < NoOfSegments; i++) {
		UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(this);
		Mesh->SetStaticMesh(WallMesh);
		Mesh->RegisterComponent();
		Mesh->AttachToComponent(Scene, FAttachmentTransformRules::KeepRelativeTransform);
		Mesh->SetRelativeLocation(FVector( i*300 , 0,0 ));
		WallArray.Add(Mesh);
	}
}

void AWallGenerator::ClearWalls()
{
	for (auto it : WallArray) {
		if (it) {
			it->DestroyComponent();
			it = nullptr;
		}
	}

	WallArray.Empty();
}

void AWallGenerator::HighlightWalls()
{

	for (auto it : WallArray) {
		if (it) {
			it->SetRenderCustomDepth(true);
			it->CustomDepthStencilValue = 2.0;
		}
	}

}

void AWallGenerator::DeHighlightWalls()
{
	for (auto it : WallArray) {
		if (it) {
			it->SetRenderCustomDepth(false);
		}
	}
}

void AWallGenerator::HighlightWall()
{
	if (WallSegment) {
		WallSegment->SetRenderCustomDepth(true);
		WallSegment->CustomDepthStencilValue = 2.0;
	}
}

void AWallGenerator::DeHighlightWall()
{
	if (WallSegment) {
		WallSegment->SetRenderCustomDepth(false);
	}
}

void AWallGenerator::SetMaterial(UMaterialInterface* Material)
{
	for (auto it : WallArray) {
		if (it) {
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::FromInt(it->GetMaterials().Num()));

			if (it->GetMaterials().Num() == 1) {
				it->SetMaterial(0 , Material);
			}
			else if (it->GetMaterials().Num() == 2) {
				it->SetMaterial(1, Material);
			}
			else if (it->GetMaterials().Num() == 3) {
				it->SetMaterial(1, Material);
				it->SetMaterial(2, Material);
			}
			else if (it->GetMaterials().Num() == 4) {
				it->SetMaterial(3, Material);
			}
		}
	}
}

UMaterialInterface* AWallGenerator::GetMaterial(UStaticMeshComponent* MeshComponent)
{
	auto index = MeshComponent->GetMaterials().Num();
	switch (index) {
	case 1:
		return MeshComponent->GetMaterial(0);
		break;

	case 2:
		return MeshComponent->GetMaterial(1);
		break;

	case 3:
		return MeshComponent->GetMaterial(1);
		break;

	case 4:
		return MeshComponent->GetMaterial(3);
		break;
	}

	return nullptr;
}

void AWallGenerator::SetWallSegment(UStaticMeshComponent* Segment)
{
	WallSegment = Segment;
}

UStaticMeshComponent* AWallGenerator::GetWallSegment()
{
	if (WallSegment) return WallSegment;
	else return nullptr;
}

void AWallGenerator::UpdateWallSegment(FVector Location , UStaticMesh* Mesh)
{
	auto index = WallArray.Find(WallSegment);

	if (index != INDEX_NONE) {
		WallArray[index]->DestroyComponent();
		WallSegment->SetStaticMesh(Mesh);
		WallSegment->RegisterComponent();
		WallSegment->AttachToComponent(Scene, FAttachmentTransformRules::KeepRelativeTransform);
		WallSegment->SetRelativeLocation(Location);

		WallArray[index] = WallSegment;
	}
}

void AWallGenerator::EndPlay(EEndPlayReason::Type Reason)
{
	ClearWalls();
	Super::EndPlay(Reason);
}

void AWallGenerator::GenerateDoor(UStaticMesh* DoorMesh)
{
	if (WallSegment) {
		auto location = WallSegment->GetRelativeLocation();

		UMaterialInterface* DefaultMaterial = GetMaterial(WallSegment);

		int32 ArrayIndex = WallArray.Find(WallSegment);

		WallSegment->DestroyComponent();
		WallSegment = nullptr;

		UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(this);
		MeshComponent->SetStaticMesh(DoorMesh);
		MeshComponent->AttachToComponent(Scene, FAttachmentTransformRules::KeepRelativeTransform);
		MeshComponent->RegisterComponent();
		MeshComponent->SetRelativeLocation(location + FVector(-1, 0, 0));
		MeshComponent->SetRelativeRotation(FRotator(0, 90, 0));
		MeshComponent->SetWorldScale3D(FVector(0.2, 1.005, 1));

		WallArray[ArrayIndex] = MeshComponent;

		SetMaterial(DefaultMaterial);
	}
}

void AWallGenerator::UpdateLocation()
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

				//FVector PrevLocation = FVector(0, 0, AreaActor->GetActorLocation().Z);
				SetActorLocation(Location);

				SnapActor(this, 20);
			}
		}
}
