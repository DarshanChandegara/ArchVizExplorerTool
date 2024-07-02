// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "TemplateWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHVIZPLUGIN_API UTemplateWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteTemplateButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CompleteTemplateButton;

	UPROPERTY(meta = (BindWidget))
	UButton* Template1;

	UPROPERTY(meta = (BindWidget))
	UButton* Template2;

	UPROPERTY(meta = (BindWidget))
	UButton* Template3;
	
};
