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
						Buttontext->SetJustification(ETextJustify::Center);
						Buttontext->SetMinDesiredWidth(500);
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

	if (CloseSave) {
		CloseSave->OnClicked.AddDynamic(this, &UMainWidget::HandleCloseSaveClick);
	}

	if (NewButton) {
		NewButton->OnClicked.AddDynamic(this , &UMainWidget::HandleNewButtonClick);
	}

	if (RenameButton) {
		RenameButton->OnClicked.AddDynamic(this, &UMainWidget::HandleRenameButtonClick);
	}

	if (CloseRename) {
		CloseRename->OnClicked.AddDynamic(this, &UMainWidget::HandleCloseSaveClick);
	}

}

void UMainWidget::HandleNewButtonClick()
{
	MainCanvas->SetVisibility(ESlateVisibility::Collapsed);
	RenameButton->SetVisibility(ESlateVisibility::Collapsed);
	
	AArcWizPlayerController* PC = Cast<AArcWizPlayerController>(GetWorld()->GetFirstPlayerController());

	if (PC) {
		PC->NotifyUser("New Project Created Succesfully");
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
	AArcWizPlayerController* PC = Cast<AArcWizPlayerController>(GetWorld()->GetFirstPlayerController());

	RenameBorder->SetVisibility(ESlateVisibility::Collapsed);
	if(PC -> ProjectName == "")
	{
		SaveBorder->SetVisibility(ESlateVisibility::Visible);
		ScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	}
	else {
		ScrollBox->SetVisibility(ESlateVisibility::Collapsed);
		if(PC->SaveGame(PC->ProjectName))
			PC->NotifyUser(PC->ProjectName + " Saved Successfully");
		else 
			PC->NotifyUser(PC->ProjectName + " Didn't Save");
	}
}

void UMainWidget::HandleCloseSaveClick()
{
	SaveBorder->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainWidget::HandleCloseRenameClick()
{
	RenameBorder->SetVisibility(ESlateVisibility::Collapsed);
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
				FString Name = array[i].LeftChop(4);
				if ((Name != "Template 1") && (Name != "Template 2") && (Name != "Template 3"))
					AddChilds(Name, i);
			}
		}
	}
}

void UMainWidget::HandleRenameButtonClick()
{
	SaveBorder->SetVisibility(ESlateVisibility::Collapsed);
	RenameBorder->SetVisibility(ESlateVisibility::Visible);
}

void UMainWidget::ShowNotification(const FText& Message)
{
	NotificationBox->SetVisibility(ESlateVisibility::Visible);
	NotificationText->SetText(Message);
}

void UMainWidget::HideNotification()
{
	NotificationBox->SetVisibility(ESlateVisibility::Collapsed);
}
