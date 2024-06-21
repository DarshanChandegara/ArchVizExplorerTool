// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollBoxWidget.h"
#include <Components/HorizontalBox.h>
#include <Components/Button.h>
#include <Components/Image.h>

void UScrollBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UScrollBoxWidget::DemoCall()
{
}

void UScrollBoxWidget::initialize()
{
	if (DoorAsset) {
		if (ScrollBox) {
			ScrollBox->ClearChildren();

			for (auto DoorData : DoorAsset->DoorArray) {
				UHorizontalBox* HorizontalBox = NewObject<UHorizontalBox>(this);
				UButton* Button = NewObject<UButton>(this);
				UImage* Image = NewObject<UImage>(this);

				Image->SetBrushFromTexture(DoorData.Image);

				Button->AddChild(Image);
				HorizontalBox->AddChild(Button);
				ScrollBox->AddChild(HorizontalBox);

				Button->OnClicked.AddDynamic(this, &UScrollBoxWidget::DemoCall);
				//Button->SetUserFocus(this);
				//Button->Data
			}
		}
	}
}

