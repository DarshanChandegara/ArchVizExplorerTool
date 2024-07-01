// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ScrollBox.h>
#include "CustomButton.h"
#include <Components/ComboBoxString.h>
#include <Components/EditableText.h>
#include <Components/Border.h>
#include <Components/CanvasPanel.h>
#include "MainWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnButtonClick , int32)
DECLARE_DELEGATE_OneParam(FOnDeleteButtonClick , int32)

UCLASS()
class ARCHVIZPLUGIN_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainCanvas;

	UPROPERTY(meta = (BindWidget))
	UButton* NewButton;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ComboBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Save;

	UPROPERTY(meta = (BindWidget))
	UButton* Rename;

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RenameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LoadButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseSave;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseRename;

	UPROPERTY(meta = (BindWidget))
	UButton* InstructionButton;

	UPROPERTY(meta = (BindWidget))
	UEditableText* SaveSlotName;

	UPROPERTY(meta = (BindWidget))
	UEditableText* SaveSlotName_;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(meta = (BindWidget))
	UBorder* SaveBorder;

	UPROPERTY(meta = (BindWidget))
	UBorder* RenameBorder;

	UPROPERTY(meta = (BindWidget))
	UBorder* NotificationBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NotificationText;

	UPROPERTY( Transient , meta = (BindWidgetAnim))
	UWidgetAnimation* PopUp;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TSubclassOf<UCustomButton> ButtonClass;

	UFUNCTION(BlueprintCallable)
	void AddChilds(FString Text, int32 Id);

	FOnButtonClick ButtonClick;
	FOnDeleteButtonClick DeleteButtonClick;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleNewButtonClick();
	
	UFUNCTION()
	void BindLoadFunction(int32 data);

	UFUNCTION()
	void BindDeleteFunction(int32 data);

	UFUNCTION()
	void HandleSaveButtonClick();

	UFUNCTION()
	void HandleCloseSaveClick();

	UFUNCTION()
	void HandleCloseRenameClick();

	UFUNCTION()
	void HandleLoadButtonClick();

	UFUNCTION()
	void HandleRenameButtonClick();

	UFUNCTION(BlueprintCallable)
	void ShowNotification(const FText& Message);

	UFUNCTION(BlueprintCallable)
	void HideNotification();


};
