// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/SpinBox.h>
#include <Components/HorizontalBox.h>
#include <Components/VerticalBox.h>
#include "RoadWidget.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API URoadWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UButton* ConstructionMode;

	UPROPERTY(meta = (BindWidget))
	UButton* EditorMode;

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Width;

	UPROPERTY(meta = (BindWidget))
	USpinBox* X;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Y;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticleBox;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnConstructionModeClicked();

	UFUNCTION()
	void OnEditorModeClicked();

	UPROPERTY()
	FVector Location;

};
