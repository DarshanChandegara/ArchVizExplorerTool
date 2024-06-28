// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "ArcWizPlayerController.h"

void UMainWidget::AddChilds(FString Text, int32 Id)
{
	if (ScrollBox)
	{
		if (ButtonClass) {
			UCustomButton* Button = CreateWidget<UCustomButton>(ScrollBox, ButtonClass);

			if (Button) {
				Button->InitializeWidget(Id);

				if (Button->MyButton) {
					UTextBlock* Buttontext = NewObject<UTextBlock>(Button);
					if (Buttontext) {
						Buttontext->SetText(FText::FromString(Text));
						Button->MyButton->AddChild(Buttontext);
					}
				}
				ScrollBox->AddChild(Button);
				Button->OnButtonClick.BindUObject(this, &UMainWidget::BindLoadFunction);
				Button->OnDeleteButtonClick.BindUObject(this, &UMainWidget::BindDeleteFunction);
			}
		}
	}
}

void UMainWidget::NativeConstruct()
{
	if (SaveButton) {
		SaveButton->OnClicked.AddDynamic(this , &UMainWidget::HandleSaveButtonClick);
	}
	
	if (LoadButton) {
		LoadButton->OnClicked.AddDynamic(this , &UMainWidget::HandleLoadButtonClick);
	}

	if (Save) {
		CloseSave->OnClicked.AddDynamic(this, &UMainWidget::HandleCloseSaveClick);
	}

}

void UMainWidget::BindLoadFunction(int32 data)
{
	ButtonClick.ExecuteIfBound(data);
}

void UMainWidget::BindDeleteFunction(int32 data)
{
	DeleteButtonClick.ExecuteIfBound(data);
}

void UMainWidget::HandleSaveButtonClick()
{
	SaveBorder->SetVisibility(ESlateVisibility::Visible);
	ScrollBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainWidget::HandleCloseSaveClick()
{
	SaveBorder->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainWidget::HandleLoadButtonClick()
{
	ScrollBox->SetVisibility(ESlateVisibility::Visible);
	SaveBorder->SetVisibility(ESlateVisibility::Collapsed);
	AArcWizPlayerController* PC = Cast<AArcWizPlayerController>(GetWorld()->GetFirstPlayerController());
	ScrollBox->ClearChildren();

	if (PC) {

		FString SavedDir = FPaths::ProjectSavedDir();
		SavedDir.Append("/SaveGames");
		auto array = PC->FindFiles(SavedDir, ".sav");

		if (array.Num() == 0) {
			UButton* button = NewObject<UButton>(ScrollBox);
			if (button) {
				UTextBlock* Buttontext = NewObject<UTextBlock>(ScrollBox);
				if (Buttontext) {
					Buttontext->SetText(FText::FromString("No Projects To Load"));
					button->AddChild(Buttontext);
				}
				button->SetBackgroundColor(FColor::FromHex("#02BFFFFF"));
				ScrollBox->AddChild(button);
			}
		}
		else {
			for (int i = 0; i < array.Num(); i++) {
				PC->AddDataToLoadMap(i, array[i]);
				AddChilds(array[i].LeftChop(4), i);
			}
		}
	}
}
