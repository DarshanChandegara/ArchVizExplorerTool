// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadWidget.h"

void URoadWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URoadWidget::OnConstructionModeClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "2");

	ConstructionMode->SetVisibility(ESlateVisibility::Collapsed);
	InstructionButton->SetVisibility(ESlateVisibility::Collapsed);
	EditorMode->SetVisibility(ESlateVisibility::Visible);
	HorizontalBox->SetVisibility(ESlateVisibility::Collapsed);
	DeleteButton->SetVisibility(ESlateVisibility::Collapsed);
	VerticleBox->SetVisibility(ESlateVisibility::Collapsed);
	SaveButton->SetVisibility(ESlateVisibility::Visible);

}

void URoadWidget::OnEditorModeClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "2");

	ConstructionMode->SetVisibility(ESlateVisibility::Visible);
	InstructionButton->SetVisibility(ESlateVisibility::Visible);
	EditorMode->SetVisibility(ESlateVisibility::Collapsed);
	HorizontalBox->SetVisibility(ESlateVisibility::Visible);
	DeleteButton->SetVisibility(ESlateVisibility::Visible);
	VerticleBox->SetVisibility(ESlateVisibility::Visible);
	SaveButton->SetVisibility(ESlateVisibility::Collapsed);
}
