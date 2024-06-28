// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "CustomButton.generated.h"

DECLARE_DELEGATE_OneParam(FOnButtonClick , int32)
DECLARE_DELEGATE_OneParam(FOnDeleteButtonClick , int32)

UCLASS()
class ARCHVIZPLUGIN_API UCustomButton : public UUserWidget
{
	GENERATED_BODY()

public:

	FOnButtonClick OnButtonClick;
	FOnDeleteButtonClick OnDeleteButtonClick;

	UCustomButton(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	UButton* MyButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteSlotButton;

	UPROPERTY()
	int32 Index;

	virtual void NativeConstruct() override;

	void InitializeWidget(int32 CustomInt);

	UFUNCTION()
	void ClickButtonHandle();	

	UFUNCTION()
	void DeleteButtonHandle();	
};
