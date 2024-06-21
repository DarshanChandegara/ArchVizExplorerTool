// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DoorDataAsset.h"
#include <Components/ScrollBox.h>
#include "ScrollBoxWidget.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API UScrollBoxWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY()
	UDoorDataAsset* DoorAsset;

	void initialize();

	virtual void NativeConstruct() override;

	UFUNCTION()
	void DemoCall();
};
