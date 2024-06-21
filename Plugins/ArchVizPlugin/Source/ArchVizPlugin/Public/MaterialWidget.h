// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyScrollBoxWidget.h"
#include "MaterialWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHVIZPLUGIN_API UMaterialWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UMyScrollBoxWidget* WallMaterialScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UMyScrollBoxWidget* RoadMaterialScrollBox;
};
