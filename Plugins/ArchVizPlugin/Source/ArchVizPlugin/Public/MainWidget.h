// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ScrollBox.h>
#include "CustomButton.h"
#include <Components/ComboBoxString.h>
#include <Components/EditableText.h>
#include <Components/Border.h>
#include "MainWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnButtonClick , int32)

UCLASS()
class ARCHVIZPLUGIN_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ComboBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Save;

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LoadButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseSave;

	UPROPERTY(meta = (BindWidget))
	UButton* InstructionButton;

	UPROPERTY(meta = (BindWidget))
	UEditableText* SaveSlotName;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(meta = (BindWidget))
	UBorder* SaveBorder;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TSubclassOf<UCustomButton> ButtonClass;

	UFUNCTION(BlueprintCallable)
	void AddChilds(FString Text, int32 Id);

	FOnButtonClick ButtonClick;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void BindFunction(int32 data);

	UFUNCTION()
	void HandleSaveButtonClick();

	UFUNCTION()
	void HandleCloseSaveClick();

	UFUNCTION()
	void HandleLoadButtonClick();
};
