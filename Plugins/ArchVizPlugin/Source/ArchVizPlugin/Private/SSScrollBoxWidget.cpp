// Fill out your copyright notice in the Description page of Project Settings.


#include "SSScrollBoxWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSScrollBoxWidget::Construct(const FArguments& InArgs)
{
	DataAssetManager = InArgs._InDataAssetManager;
	AssetType = InArgs._InAssetType;
	ImageSize = InArgs._InImageSize;
	HeadTextSize = InArgs._InHeadTextSize;
	HeadString = InArgs._InHeadText;
	ThumbnailTextSize = InArgs._InThumbnailTextSize;
	BGColor = InArgs._InBGColor;

	TSharedPtr<SBorder> RootBorder = SNew(SBorder);

	RootVerticalBox = SNew(SVerticalBox);

	FSlateBrush* BorderImage = new FSlateBrush();
	BorderImage->DrawAs = ESlateBrushDrawType::Type::RoundedBox;
	FSlateBrushOutlineSettings OutlineSettings{};
	OutlineSettings.CornerRadii = FVector4{ 5,5,5,5 };
	OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
	BorderImage->OutlineSettings = OutlineSettings;

	RootBorder->SetBorderImage(BorderImage);
	RootBorder->SetContent(RootVerticalBox.ToSharedRef());
	//RootBorder->SetBorderBackgroundColor(FColor::FromHex("#D3D3D3FF"));
	RootBorder->SetBorderBackgroundColor(BGColor);



	ChildSlot.VAlign(EVerticalAlignment::VAlign_Center)
		[
			RootBorder.ToSharedRef()
		];

	HeadText = SNew(STextBlock).Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), HeadTextSize))
		.ColorAndOpacity(FColor::FromHex("#ffffff"));
	HeadText->SetText(FText::FromString(HeadString));

	ScrollBox = SNew(SScrollBox);
	ScrollBox->SetOrientation(EOrientation::Orient_Horizontal);
	CreateScrollBox();
}

void SSScrollBoxWidget::CreateScrollBox()
{
	ScrollBox->ClearChildren();
	switch (AssetType) {
	case EAssetType::Door:
		CreateDoorScrollBox();
		break;

	case EAssetType::RoadMaterial:
		CreateRoadMaterialScrollBox();
		break;

	case EAssetType::WallMaterial:
		CreateWallMaterialScrollBox();
		break;

	case EAssetType::Chair:
		CreateChairScrollBox();
		break;

	case EAssetType::Table:
		CreateTableScrollBox();
		break;

	case EAssetType::sofa:
		CreateSofaScrollBox();
		break;

	case EAssetType::WallInterior:
		CreateWallInteriorScrollBox();
		break;

	case EAssetType::CeilInterior:
		CreateCeilInteriorScrollBox();
		break;

	}

	
}

void SSScrollBoxWidget::CreateDoorScrollBox()
{
	if (DataAssetManager.IsValid()) {
		for (auto DoorData : DataAssetManager->DoorArray) {

			if (DoorData.Image) {
				TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);

				TSharedPtr<SBorder> ImageBorder = SNew(SBorder);

				FSlateBrush* BorderImage = new FSlateBrush();
				BorderImage->DrawAs = ESlateBrushDrawType::Type::RoundedBox;
				FSlateBrushOutlineSettings OutlineSettings{};
				OutlineSettings.CornerRadii = FVector4{ 5,5,5,5 };
				OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				BorderImage->OutlineSettings = OutlineSettings;



				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(DoorData.Image);

				if (UTexture2D* newThumbnail = Cast<UTexture2D>(DoorData.Image))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Success");

					ThumbnailBrush->SetImageSize(FVector2D(ImageSize));
					TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).OnMouseButtonDown_Lambda([this, DoorData](const FGeometry& InGeometry, const FPointerEvent& MouseEvent) {
						if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
							OnDoorSelected.ExecuteIfBound(DoorData);
							return FReply::Handled();
						}
						return FReply::Unhandled();
						}).Cursor(EMouseCursor::Hand);

						ImageBorder->SetContent(ThumbnailImage.ToSharedRef());
						ImageBorder->SetBorderImage(BorderImage);
						ImageBorder->SetBorderBackgroundColor(FColor::Cyan);

						VerticalBox->AddSlot()
							[
								ImageBorder.ToSharedRef()
							];
				}


				TSharedPtr<STextBlock> TextBlock = SNew(STextBlock).Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), ThumbnailTextSize))
					.ColorAndOpacity(FSlateColor(FColor::FromHex("#ffffff")));;
				TextBlock->SetText(FText::FromString(DoorData.Name));
				VerticalBox->AddSlot().HAlign(EHorizontalAlignment::HAlign_Center).AutoHeight()
					[
						TextBlock.ToSharedRef()
					];

				ScrollBox->AddSlot().VAlign(EVerticalAlignment::VAlign_Center).Padding(FVector2D(5))
					[
						VerticalBox.ToSharedRef()
					];
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Doors");

		}
	}

	RootVerticalBox->AddSlot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Center)
		[
			HeadText.ToSharedRef()
		];

	RootVerticalBox->AddSlot().AutoHeight()
		[
			ScrollBox.ToSharedRef()
		];
}

void SSScrollBoxWidget::CreateRoadMaterialScrollBox()
{
	if (DataAssetManager.IsValid()) {
		for (auto RoadData : DataAssetManager->RoadMaterialArray) {

			if (RoadData.Image) {
				TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);

				TSharedPtr<SBorder> ImageBorder = SNew(SBorder);

				FSlateBrush* BorderImage = new FSlateBrush();
				BorderImage->DrawAs = ESlateBrushDrawType::Type::RoundedBox;
				FSlateBrushOutlineSettings OutlineSettings{};
				OutlineSettings.CornerRadii = FVector4{ 5,5,5,5 };
				OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				BorderImage->OutlineSettings = OutlineSettings;



				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(RoadData.Image);

				if (UTexture2D* newThumbnail = Cast<UTexture2D>(RoadData.Image))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Success");

					ThumbnailBrush->SetImageSize(FVector2D(ImageSize));
					TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).OnMouseButtonDown_Lambda([this, RoadData](const FGeometry& InGeometry, const FPointerEvent& MouseEvent) {
						if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
							OnRoadSelected.ExecuteIfBound(RoadData);
							return FReply::Handled();
						}
						return FReply::Unhandled();
						}).Cursor(EMouseCursor::Hand);

						ImageBorder->SetContent(ThumbnailImage.ToSharedRef());
						ImageBorder->SetBorderImage(BorderImage);
						ImageBorder->SetBorderBackgroundColor(FColor::Cyan);

						VerticalBox->AddSlot()
							[
								ImageBorder.ToSharedRef()
							];
				}

				ScrollBox->AddSlot().VAlign(EVerticalAlignment::VAlign_Center).Padding(FVector2D(5))
					[
						VerticalBox.ToSharedRef()
					];
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Doors");

		}
	}

	RootVerticalBox->AddSlot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Center)
		[
			HeadText.ToSharedRef()
		];

	RootVerticalBox->AddSlot().AutoHeight()
		[
			ScrollBox.ToSharedRef()
		];
}

void SSScrollBoxWidget::CreateWallMaterialScrollBox()
{
	if (DataAssetManager.IsValid()) {
		for (auto WallData : DataAssetManager->WallMaterialArray) {

			if (WallData.Image) {
				TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);

				TSharedPtr<SBorder> ImageBorder = SNew(SBorder);

				FSlateBrush* BorderImage = new FSlateBrush();
				BorderImage->DrawAs = ESlateBrushDrawType::Type::RoundedBox;
				FSlateBrushOutlineSettings OutlineSettings{};
				OutlineSettings.CornerRadii = FVector4{ 5,5,5,5 };
				OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				BorderImage->OutlineSettings = OutlineSettings;



				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(WallData.Image);

				if (UTexture2D* newThumbnail = Cast<UTexture2D>(WallData.Image))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Success");

					ThumbnailBrush->SetImageSize(FVector2D(ImageSize));
					TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).OnMouseButtonDown_Lambda([this, WallData](const FGeometry& InGeometry, const FPointerEvent& MouseEvent) {
						if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
							OnWallSelected.ExecuteIfBound(WallData);
							return FReply::Handled();
						}
						return FReply::Unhandled();
						}).Cursor(EMouseCursor::Hand);

						ImageBorder->SetContent(ThumbnailImage.ToSharedRef());
						ImageBorder->SetBorderImage(BorderImage);
						ImageBorder->SetBorderBackgroundColor(FColor::Cyan);

						VerticalBox->AddSlot()
							[
								ImageBorder.ToSharedRef()
							];
				}

				ScrollBox->AddSlot().VAlign(EVerticalAlignment::VAlign_Center).Padding(FVector2D(5))
					[
						VerticalBox.ToSharedRef()
					];
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Doors");

		}
	}

	RootVerticalBox->AddSlot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Center)
		[
			HeadText.ToSharedRef()
		];

	RootVerticalBox->AddSlot().AutoHeight()
		[
			ScrollBox.ToSharedRef()
		];
}

void SSScrollBoxWidget::CreateChairScrollBox()
{
	if (DataAssetManager.IsValid()) {
		for (auto ChairData : DataAssetManager->ChairArray) {

			if (ChairData.Image) {
				TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);

				TSharedPtr<SBorder> ImageBorder = SNew(SBorder);

				FSlateBrush* BorderImage = new FSlateBrush();
				BorderImage->DrawAs = ESlateBrushDrawType::Type::RoundedBox;
				FSlateBrushOutlineSettings OutlineSettings{};
				OutlineSettings.CornerRadii = FVector4{ 5,5,5,5 };
				OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				BorderImage->OutlineSettings = OutlineSettings;



				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(ChairData.Image);

				if (UTexture2D* newThumbnail = Cast<UTexture2D>(ChairData.Image))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Success");

					ThumbnailBrush->SetImageSize(FVector2D(ImageSize));
					TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).OnMouseButtonDown_Lambda([this, ChairData](const FGeometry& InGeometry, const FPointerEvent& MouseEvent) {
						if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
							OnStaticMeshSelected.ExecuteIfBound(ChairData);
							return FReply::Handled();
						}
						return FReply::Unhandled();
						}).Cursor(EMouseCursor::Hand);

						ImageBorder->SetContent(ThumbnailImage.ToSharedRef());
						ImageBorder->SetBorderImage(BorderImage);
						ImageBorder->SetBorderBackgroundColor(FColor::Cyan);

						VerticalBox->AddSlot()
							[
								ImageBorder.ToSharedRef()
							];
				}

				ScrollBox->AddSlot().VAlign(EVerticalAlignment::VAlign_Center).Padding(FVector2D(5))
					[
						VerticalBox.ToSharedRef()
					];
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Doors");

		}
	}

	RootVerticalBox->AddSlot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Center)
		[
			HeadText.ToSharedRef()
		];

	RootVerticalBox->AddSlot().AutoHeight()
		[
			ScrollBox.ToSharedRef()
		];
}

void SSScrollBoxWidget::CreateTableScrollBox()
{
	if (DataAssetManager.IsValid()) {
		for (auto TableData : DataAssetManager->TableArray) {

			if (TableData.Image) {
				TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);

				TSharedPtr<SBorder> ImageBorder = SNew(SBorder);

				FSlateBrush* BorderImage = new FSlateBrush();
				BorderImage->DrawAs = ESlateBrushDrawType::Type::RoundedBox;
				FSlateBrushOutlineSettings OutlineSettings{};
				OutlineSettings.CornerRadii = FVector4{ 5,5,5,5 };
				OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				BorderImage->OutlineSettings = OutlineSettings;



				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(TableData.Image);

				if (UTexture2D* newThumbnail = Cast<UTexture2D>(TableData.Image))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Success");

					ThumbnailBrush->SetImageSize(FVector2D(ImageSize));
					TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).OnMouseButtonDown_Lambda([this, TableData](const FGeometry& InGeometry, const FPointerEvent& MouseEvent) {
						if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
							OnStaticMeshSelected.ExecuteIfBound(TableData);
							return FReply::Handled();
						}
						return FReply::Unhandled();
						}).Cursor(EMouseCursor::Hand);

						ImageBorder->SetContent(ThumbnailImage.ToSharedRef());
						ImageBorder->SetBorderImage(BorderImage);
						ImageBorder->SetBorderBackgroundColor(FColor::Cyan);

						VerticalBox->AddSlot()
							[
								ImageBorder.ToSharedRef()
							];
				}

				ScrollBox->AddSlot().VAlign(EVerticalAlignment::VAlign_Center).Padding(FVector2D(5))
					[
						VerticalBox.ToSharedRef()
					];
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Doors");

		}
	}

	RootVerticalBox->AddSlot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Center)
		[
			HeadText.ToSharedRef()
		];

	RootVerticalBox->AddSlot().AutoHeight()
		[
			ScrollBox.ToSharedRef()
		];
}

void SSScrollBoxWidget::CreateSofaScrollBox()
{
	if (DataAssetManager.IsValid()) {
		for (auto SofaData : DataAssetManager->SofaArray) {

			if (SofaData.Image) {
				TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);

				TSharedPtr<SBorder> ImageBorder = SNew(SBorder);

				FSlateBrush* BorderImage = new FSlateBrush();
				BorderImage->DrawAs = ESlateBrushDrawType::Type::RoundedBox;
				FSlateBrushOutlineSettings OutlineSettings{};
				OutlineSettings.CornerRadii = FVector4{ 5,5,5,5 };
				OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				BorderImage->OutlineSettings = OutlineSettings;



				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(SofaData.Image);

				if (UTexture2D* newThumbnail = Cast<UTexture2D>(SofaData.Image))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Success");

					ThumbnailBrush->SetImageSize(FVector2D(ImageSize));
					TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).OnMouseButtonDown_Lambda([this, SofaData](const FGeometry& InGeometry, const FPointerEvent& MouseEvent) {
						if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
							OnStaticMeshSelected.ExecuteIfBound(SofaData);
							return FReply::Handled();
						}
						return FReply::Unhandled();
						}).Cursor(EMouseCursor::Hand);

						ImageBorder->SetContent(ThumbnailImage.ToSharedRef());
						ImageBorder->SetBorderImage(BorderImage);
						ImageBorder->SetBorderBackgroundColor(FColor::Cyan);

						VerticalBox->AddSlot()
							[
								ImageBorder.ToSharedRef()
							];
				}

				ScrollBox->AddSlot().VAlign(EVerticalAlignment::VAlign_Center).Padding(FVector2D(5))
					[
						VerticalBox.ToSharedRef()
					];
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Doors");

		}
	}

	RootVerticalBox->AddSlot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Center)
		[
			HeadText.ToSharedRef()
		];

	RootVerticalBox->AddSlot().AutoHeight()
		[
			ScrollBox.ToSharedRef()
		];
}

void SSScrollBoxWidget::CreateWallInteriorScrollBox() {
	if (DataAssetManager.IsValid()) {
		for (auto WallInteriorData : DataAssetManager->WallInteriorArray) {

			if (WallInteriorData.Image) {
				TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);

				TSharedPtr<SBorder> ImageBorder = SNew(SBorder);

				FSlateBrush* BorderImage = new FSlateBrush();
				BorderImage->DrawAs = ESlateBrushDrawType::Type::RoundedBox;
				FSlateBrushOutlineSettings OutlineSettings{};
				OutlineSettings.CornerRadii = FVector4{ 5,5,5,5 };
				OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				BorderImage->OutlineSettings = OutlineSettings;



				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(WallInteriorData.Image);

				if (UTexture2D* newThumbnail = Cast<UTexture2D>(WallInteriorData.Image))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Success");

					ThumbnailBrush->SetImageSize(FVector2D(ImageSize));
					TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).OnMouseButtonDown_Lambda([this, WallInteriorData](const FGeometry& InGeometry, const FPointerEvent& MouseEvent) {
						if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
							OnStaticMeshSelected.ExecuteIfBound(WallInteriorData);
							return FReply::Handled();
						}
						return FReply::Unhandled();
						}).Cursor(EMouseCursor::Hand);

						ImageBorder->SetContent(ThumbnailImage.ToSharedRef());
						ImageBorder->SetBorderImage(BorderImage);
						ImageBorder->SetBorderBackgroundColor(FColor::Cyan);

						VerticalBox->AddSlot()
							[
								ImageBorder.ToSharedRef()
							];
				}

				ScrollBox->AddSlot().VAlign(EVerticalAlignment::VAlign_Center).Padding(FVector2D(5))
					[
						VerticalBox.ToSharedRef()
					];
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Doors");

		}
	}

	RootVerticalBox->AddSlot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Center)
		[
			HeadText.ToSharedRef()
		];

	RootVerticalBox->AddSlot().AutoHeight()
		[
			ScrollBox.ToSharedRef()
		];
}

void SSScrollBoxWidget::CreateCeilInteriorScrollBox() {
	if (DataAssetManager.IsValid()) {
		for (auto CeilInteriorData : DataAssetManager->CeilInteriorArray) {

			if (CeilInteriorData.Image) {
				TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);

				TSharedPtr<SBorder> ImageBorder = SNew(SBorder);

				FSlateBrush* BorderImage = new FSlateBrush();
				BorderImage->DrawAs = ESlateBrushDrawType::Type::RoundedBox;
				FSlateBrushOutlineSettings OutlineSettings{};
				OutlineSettings.CornerRadii = FVector4{ 5,5,5,5 };
				OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
				BorderImage->OutlineSettings = OutlineSettings;



				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(CeilInteriorData.Image);

				if (UTexture2D* newThumbnail = Cast<UTexture2D>(CeilInteriorData.Image))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Success");

					ThumbnailBrush->SetImageSize(FVector2D(ImageSize));
					TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).OnMouseButtonDown_Lambda([this, CeilInteriorData](const FGeometry& InGeometry, const FPointerEvent& MouseEvent) {
						if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
							OnStaticMeshSelected.ExecuteIfBound(CeilInteriorData);
							return FReply::Handled();
						}
						return FReply::Unhandled();
						}).Cursor(EMouseCursor::Hand);

						ImageBorder->SetContent(ThumbnailImage.ToSharedRef());
						ImageBorder->SetBorderImage(BorderImage);
						ImageBorder->SetBorderBackgroundColor(FColor::Cyan);

						VerticalBox->AddSlot()
							[
								ImageBorder.ToSharedRef()
							];
				}

				ScrollBox->AddSlot().VAlign(EVerticalAlignment::VAlign_Center).Padding(FVector2D(5))
					[
						VerticalBox.ToSharedRef()
					];
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Doors");

		}
	}

	RootVerticalBox->AddSlot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Center)
		[
			HeadText.ToSharedRef()
		];

	RootVerticalBox->AddSlot().AutoHeight()
		[
			ScrollBox.ToSharedRef()
		];
}



END_SLATE_FUNCTION_BUILD_OPTIMIZATION

