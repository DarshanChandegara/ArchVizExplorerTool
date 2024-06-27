// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomButton.h"

UCustomButton::UCustomButton(const FObjectInitializer& ObjectInitializer) :Super (ObjectInitializer)
{
}

void UCustomButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (MyButton) {
		MyButton->OnClicked.AddDynamic(this , &UCustomButton::ClickButtonHandle);
	}
}

void UCustomButton::InitializeWidget(int32 CustomInt)
{
	Index = CustomInt;
}

void UCustomButton::ClickButtonHandle()
{
	OnButtonClick.ExecuteIfBound(Index);
}

