// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "SSScrollBoxWidget.h"
#include "MyScrollBoxWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnDoorSelectEvent, const FDoorType&)
DECLARE_DELEGATE_OneParam(FOnWallSelectEvent, const FWallMaterial&)
DECLARE_DELEGATE_OneParam(FOnRoadSelectEvent, const FRoadMaterial&)
DECLARE_DELEGATE_OneParam(FOnStaticMeshSelectEvent, const FStaticMeshtype&)

UCLASS()
class ARCHVIZPLUGIN_API UMyScrollBoxWidget : public UWidget
{
	GENERATED_BODY()
public:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual const FText GetPaletteCategory() override;
	virtual void ReleaseSlateResources(bool breleaseresource) override;

	TSharedPtr<SSScrollBoxWidget> ScrollBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataAssetManager* DataAssetManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EAssetType> AssetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HeadTextSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HeadText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ThumbnailTextSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateColor BGColor;


	FOnDoorSelectEvent OnDoorSelectEvent;
	FOnWallSelectEvent OnWallSelectedEvent;
	FOnRoadSelectEvent OnRoadSelectedEvent;
	FOnStaticMeshSelectEvent OnStaticMeshSelectEvent;

	void HandleOnDoorSelected(const FDoorType& DoorData);
	void HandleOnWallSelected(const FWallMaterial& WallData);
	void HandleOnRoadSelected(const FRoadMaterial& RoadData);
	void HandleOnStaticMeshSelected(const FStaticMeshtype& TableData);
};
