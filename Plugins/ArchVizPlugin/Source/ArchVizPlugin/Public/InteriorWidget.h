// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "MyScrollBoxWidget.h"
#include "InteriorWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHVIZPLUGIN_API UInteriorWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UButton* ChairButton;

	UPROPERTY(meta = (BindWidget))
	UButton* TableButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SofaButton;

	UPROPERTY(meta = (BindWidget))
	UButton* WallInterior;

	UPROPERTY(meta = (BindWidget))
	UButton* CeilInterior;

	UPROPERTY(meta = (BindWidget))
	UButton* MoveInteriorButton;

	UPROPERTY(meta = (BindWidget))
	UMyScrollBoxWidget* ChairScrollBox;

	UPROPERTY(meta = (BindWidget))
	UMyScrollBoxWidget* TableScrollBox;

	UPROPERTY(meta = (BindWidget))
	UMyScrollBoxWidget* SofaScrollBox;

	UPROPERTY(meta = (BindWidget))
	UMyScrollBoxWidget* WallInteriorScrollBox;

	UPROPERTY(meta = (BindWidget))
	UMyScrollBoxWidget* CeilInteriorScrollBox;

};
