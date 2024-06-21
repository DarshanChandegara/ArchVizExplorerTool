// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Widgets/Layout/SScrollBox.h>
#include "DataAssetManager.h"
#include "Widgets/SCompoundWidget.h"

UENUM()
enum class EAssetType : int8 {
	Door ,
	RoadMaterial
};

DECLARE_DELEGATE_OneParam(FOnDoorSelected, const FDoorType& DoorData)

class ARCHVIZPLUGIN_API SSScrollBoxWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSScrollBoxWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<UDataAssetManager>, InDataAssetManager)
	SLATE_ARGUMENT(TEnumAsByte<EAssetType>, InAssetType)
	SLATE_ARGUMENT(int, InImageSize)
	SLATE_ARGUMENT(int, InHeadTextSize)
	SLATE_ARGUMENT(FString, InHeadText)
	SLATE_ARGUMENT(int, InThumbnailTextSize)
	SLATE_ARGUMENT(FSlateColor, InBGColor)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<UDataAssetManager> DataAssetManager;
	TEnumAsByte<EAssetType> AssetType;
	int ImageSize;
	int HeadTextSize;
	FString HeadString;
	int ThumbnailTextSize;
	FSlateColor BGColor;

	FOnDoorSelected OnDoorSelected;


	TSharedPtr<SScrollBox> ScrollBox;
	TSharedPtr<SVerticalBox> RootVerticalBox;
	TSharedPtr<STextBlock> HeadText;

	void CreateScrollBox();


	void CreateDoorScrollBox();
	void CreateRoadMaterialScrollBox();

};

