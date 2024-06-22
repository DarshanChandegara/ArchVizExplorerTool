// Fill out your copyright notice in the Description page of Project Settings.


#include "MyScrollBoxWidget.h"

TSharedRef<SWidget> UMyScrollBoxWidget::RebuildWidget()
{
	ScrollBar = SNew(SSScrollBoxWidget).InDataAssetManager(DataAssetManager).InAssetType(AssetType).InImageSize(ImageSize).InHeadTextSize(HeadTextSize).InHeadText(HeadText).InThumbnailTextSize(ThumbnailTextSize).InBGColor(BGColor);
	if (ScrollBar) {
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue , "Scroll");
		ScrollBar->OnDoorSelected.BindUObject(this, &UMyScrollBoxWidget::HandleOnDoorSelected);
		ScrollBar->OnWallSelected.BindUObject(this, &UMyScrollBoxWidget::HandleOnWallSelected);
		ScrollBar->OnRoadSelected.BindUObject(this, &UMyScrollBoxWidget::HandleOnRoadSelected);
		ScrollBar->OnStaticMeshSelected.BindUObject(this, &UMyScrollBoxWidget::HandleOnStaticMeshSelected);
	}
	return ScrollBar.ToSharedRef();
}

const FText UMyScrollBoxWidget::GetPaletteCategory()
{
	Super::GetPaletteCategory();
	return FText::FromString("Panel");
}

void UMyScrollBoxWidget::ReleaseSlateResources(bool breleaseresource)
{
	Super::ReleaseSlateResources(breleaseresource);
	if (ScrollBar) {
		ScrollBar.Reset();
	}
}

void UMyScrollBoxWidget::HandleOnDoorSelected(const FDoorType& DoorData)
{
	OnDoorSelectEvent.ExecuteIfBound(DoorData);
}

void UMyScrollBoxWidget::HandleOnWallSelected(const FWallMaterial& WallData)
{
	OnWallSelectedEvent.ExecuteIfBound(WallData);
}

void UMyScrollBoxWidget::HandleOnRoadSelected(const FRoadMaterial& RoadData)
{
	OnRoadSelectedEvent.ExecuteIfBound(RoadData);
}


void UMyScrollBoxWidget::HandleOnStaticMeshSelected(const FStaticMeshtype& MeshData)
{
	OnStaticMeshSelectEvent.ExecuteIfBound(MeshData);
}
