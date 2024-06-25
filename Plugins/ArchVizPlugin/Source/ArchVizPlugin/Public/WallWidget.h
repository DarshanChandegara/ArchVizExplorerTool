// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/SpinBox.h>
#include "MyScrollBoxWidget.h"
#include <Components/Button.h>
#include <Components/HorizontalBox.h>
#include "WallWidget.generated.h"


UCLASS()
class ARCHVIZPLUGIN_API UWallWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	USpinBox* SegmentNumber;

	UPROPERTY(meta = (BindWidget))
	UButton* WallButton;

	UPROPERTY(meta = (BindWidget))
	UButton* FloorButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RoofButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DoorButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ViewButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AdjustButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MoveButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteDoorButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* RoofLengthBox;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* RoofWidthBox;
		
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* RoofHeightBox;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* OffsetBoxX;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* OffsetBoxY;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* OffsetBoxZ;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Width;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Length;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Height;

	UPROPERTY(meta = (BindWidget))
	USpinBox* XOffset;

	UPROPERTY(meta = (BindWidget))
	USpinBox* YOffset;

	UPROPERTY(meta = (BindWidget))
	USpinBox* ZOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (BindWidget))
	UMyScrollBoxWidget* DoorScrollBox;

	virtual void NativeConstruct() override;

};
