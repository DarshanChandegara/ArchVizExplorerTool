// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcWizPlayerController.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Kismet/KismetMathLibrary.h>


void AArcWizPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	RoadCreationMapping = NewObject<UInputMappingContext>(this);

	RoadGenerateAction = NewObject<UInputAction>(this);
	RoadGenerateAction->ValueType = EInputActionValueType::Boolean;
	RoadCreationMapping->MapKey(RoadGenerateAction, EKeys::LeftMouseButton);


	WallGenerationMapping = NewObject<UInputMappingContext>(this);

	WallGenerateAction = NewObject<UInputAction>(this);
	WallGenerateAction->ValueType = EInputActionValueType::Boolean;
	WallGenerationMapping->MapKey(WallGenerateAction, EKeys::LeftMouseButton);


	RotateAction = NewObject<UInputAction>(this);
	RotateAction->ValueType = EInputActionValueType::Boolean;
	WallGenerationMapping->MapKey(RotateAction, EKeys::R);


	DoorMapping = NewObject<UInputMappingContext>(this);

	LeftClickAction = NewObject<UInputAction>(this);
	LeftClickAction->ValueType = EInputActionValueType::Boolean;
	DoorMapping->MapKey(LeftClickAction, EKeys::LeftMouseButton);

	AdjustmentMapping = NewObject<UInputMappingContext>(this);

	AdjustAction = NewObject<UInputAction>(this);
	AdjustAction->ValueType = EInputActionValueType::Boolean;
	AdjustmentMapping->MapKey(AdjustAction, EKeys::LeftMouseButton);

	DeSelectAction = NewObject<UInputAction>(this);
	DeSelectAction->ValueType = EInputActionValueType::Boolean;
	AdjustmentMapping->MapKey(DeSelectAction, EKeys::BackSpace);


	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
	if (EIC) {

		EIC->BindAction(RoadGenerateAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::RoadGenerateFucntion);
		EIC->BindAction(WallGenerateAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::SpawnAndGenerate);
		EIC->BindAction(RotateAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::RotateFunction);
		EIC->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::DoorGenerationFunction);
		EIC->BindAction(AdjustAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::AdjustmentFunction);
		EIC->BindAction(DeSelectAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::DeSelectFunction);


	}
}

void AArcWizPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;

	if (RoadWidgetClass) {
		RoadWidget = CreateWidget<URoadWidget>(this, RoadWidgetClass);
	}

	if (WallWidgetClass) {
		WallWidget = CreateWidget<UWallWidget>(this, WallWidgetClass);
	}
}

void AArcWizPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Wall && !bAdjustMode) {
		if (isMoving) {
			if (FVector StartLocation_, WorldDirection; DeprojectMousePositionToWorld(StartLocation_, WorldDirection))
			{
				FVector EndLocation_ = StartLocation + WorldDirection * 100000;

				FCollisionQueryParams Params;
				Params.bTraceComplex = true;
				Params.AddIgnoredActor(Wall);

				if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation_, EndLocation_,
					ECC_Visibility, Params))
				{
					FVector Location = HitResult.Location;
			
					//FVector PrevLocation = FVector(0, 0, AreaActor->GetActorLocation().Z);
					Wall->SetActorLocation(Location);

					SnapActor(Wall, 20);
				}
			}
		}
	}

	if (Roof && !bAdjustMode) {
		if (isMoving) {
			if (FVector StartLocation_, WorldDirection; DeprojectMousePositionToWorld(StartLocation_, WorldDirection))
			{
				FVector EndLocation_ = StartLocation + WorldDirection * 100000;

				FCollisionQueryParams Params;
				Params.bTraceComplex = true;
				Params.AddIgnoredActor(Roof);

				if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation_, EndLocation_,
					ECC_Visibility, Params))
				{
					FVector Location = HitResult.Location;
					//Location.Z += WallWidget->ZOffset->GetValue();
					Roof->SetActorLocation(Location);

					SnapActor(Roof, 20);
				}
			}
		}
	}
}


void AArcWizPlayerController::HandleModeChange(FString mode)
{
	if (mode == "Road Generation") ModeType = EMode::RoadMode;
	else if (mode == "House Builder") ModeType = EMode::HouseMode;
	else if (mode == "Interior Design") ModeType = EMode::InteriorMode;
	else ModeType = EMode::MaterialMode;


	switch (ModeType) {
	case EMode::RoadMode:
	{
		if (Wall) Wall->Destroy();
		if (Roof) Roof->Destroy();
		isMoving = false;

		WallWidget->RemoveFromParent();
		RoadWidget->AddToViewport();
		if (RoadWidget) {
			RoadWidget->ConstructionMode->OnClicked.AddDynamic(this, &AArcWizPlayerController::OnConstructionModeClicked);
			RoadWidget->EditorMode->OnClicked.AddDynamic(this, &AArcWizPlayerController::OnEditorModeClicked);
			RoadWidget->Width->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::OnWidthChanged);
			RoadWidget->DeleteButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::DeleteRoad);
			RoadWidget->X->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::OnXChange);
			RoadWidget->Y->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::OnYChange);
			RoadWidget->SaveButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::NewRoadGenerateFucntion);
		}
		ULocalPlayer* LocalPlayer = GetLocalPlayer();
		check(LocalPlayer);

		if (LocalPlayer) {

			UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			check(Subsystem);

			if (Subsystem) {

				Subsystem->RemoveMappingContext(WallGenerationMapping);
				Subsystem->AddMappingContext(RoadCreationMapping, 0);
			}
		}
	}
	break;

	case EMode::HouseMode:
	{
		if (Road) Road->DeHighlightRoad();
		RoadWidget->RemoveFromParent();
		WallWidget->AddToViewport();

		if (WallWidget) {
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Valid");
			WallWidget->WallButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::WallMode);
			WallWidget->DoorButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::DoorMode);
			WallWidget->RoofButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::RoofMode);
			WallWidget->FloorButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::RoofMode);
			WallWidget->ViewButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::ViewMode);
			WallWidget->AdjustButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::AdjustMode);

			WallWidget->SegmentNumber->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleSegmentChange);

			WallWidget->Length->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleLengthChange);
			WallWidget->Width->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleWidthChange);
			WallWidget->Height->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleHeightChange);

			WallWidget->XOffset->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleXOffsetChange);
			WallWidget->YOffset->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleYOffsetChange);
			WallWidget->ZOffset->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleZOffsetChange);

			WallWidget->DoorScrollBox->OnDoorSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleDoorSelect);
			WallWidget->DeleteButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::DeleteObject);
		}
	}
	break;

	case EMode::InteriorMode:
		break;

	case EMode::MaterialMode:
		break;
	}
}

void AArcWizPlayerController::RoadGenerateFucntion()
{

	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

	if (HitResult.bBlockingHit)
	{

		if (bEditMode == false) {
			FVector ClickLocation = HitResult.Location;


			if (!DoGenerate) {
				StartLocation = ClickLocation;
				DoGenerate = true;
			}
			else if (DoGenerate) {

				FVector Offset(0, 0, 0);
				FVector Direction;


				if (SecondGeneration == false) {

					EndLocation = ClickLocation;
					Dimension.X = (EndLocation - StartLocation).Length();
					Dimension.Y = Width;
					Dimension.Z = 5;
					Direction = (EndLocation - StartLocation).GetSafeNormal();

					SpawnAndGenerateRoad(Dimension);

					SecondGeneration = true;
				}
				else {

					Direction = (EndLocation - StartLocation).GetSafeNormal();
					FVector LeftVector = FVector::CrossProduct(Direction, FVector::UpVector);
					FVector RightVector = FVector::CrossProduct(FVector::UpVector, Direction);

					PrevLocation = StartLocation;
					StartLocation = EndLocation;
					EndLocation = ClickLocation;

					Dimension.X = FVector::Distance(StartLocation, EndLocation);
					Dimension.Y = Width;
					Dimension.Z = 5;

					float Distance = FVector::Distance(EndLocation, StartLocation);

					FVector EndPointDir;

					float angle = GetAngle(Direction, (EndLocation - StartLocation));

					if (OnRightOrleft(StartLocation, EndLocation, PrevLocation)) {
						if (angle >= 0 && angle <= 45) {
							EndPointDir = Direction;
						}
						else if (angle > 45 && angle < 180) {
							EndPointDir = LeftVector;
						}
					}
					else {
						if (angle >= 0 && angle <= 45) {
							EndPointDir = Direction;
						}
						else if (angle > 45 && angle < 180) {
							EndPointDir = RightVector;
						}
					}

					EndLocation = StartLocation + (EndPointDir.GetSafeNormal() * Distance) + Offset;
					SpawnAndGenerateRoad(Dimension);
				}
			}
		}
		else {
			ARoadGenerator* SelectActor;
			if (Road) Road->DeHighlightRoad();
			if (SelectActor = Cast<ARoadGenerator>(HitResult.GetActor()); SelectActor) {
				Road = SelectActor;
				Road->HighlightRoad();	
				RoadWidget->Location = Road->GetActorLocation();
				RoadWidget->X->SetValue(RoadWidget->Location.X);
				RoadWidget->Y->SetValue(RoadWidget->Location.Y);
			}
		}
	}
}

void AArcWizPlayerController::NewRoadGenerateFucntion()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Bind");
	if(Road)
		Road->DeHighlightRoad();

	if (bEditMode == false) {
		DoGenerate = false;
		SecondGeneration = false;
		StartLocation = FVector::ZeroVector;
		EndLocation = FVector::ZeroVector;
	}
}

void AArcWizPlayerController::RotateFunction()
{
	if (Wall) {
		Wall->SetActorRelativeRotation(Wall->GetActorRotation() + FRotator(0, 90, 0));
	}
}

void AArcWizPlayerController::SetVisibility()
{
	WallWidget->HorizontalBox->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->RoofHeightBox->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->RoofLengthBox->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->RoofWidthBox->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->OffsetBoxX->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->OffsetBoxY->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->OffsetBoxZ->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->DoorScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->DeleteButton->SetVisibility(ESlateVisibility::Collapsed);

	switch (HouseConstructionMode)
	{
	case EHouseConstructionMode::Wall:
		WallWidget->HorizontalBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EHouseConstructionMode::Roof:
		WallWidget->RoofHeightBox->SetVisibility(ESlateVisibility::Visible);
		WallWidget->RoofLengthBox->SetVisibility(ESlateVisibility::Visible);
		WallWidget->RoofWidthBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EHouseConstructionMode::Door:
		break;

	case EHouseConstructionMode::Floor:
		WallWidget->RoofHeightBox->SetVisibility(ESlateVisibility::Visible);
		WallWidget->RoofLengthBox->SetVisibility(ESlateVisibility::Visible);
		WallWidget->RoofWidthBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EHouseConstructionMode::View:
		break;

	case EHouseConstructionMode::Adjust:
		WallWidget->OffsetBoxX->SetVisibility(ESlateVisibility::Visible);
		WallWidget->OffsetBoxY->SetVisibility(ESlateVisibility::Visible);
		WallWidget->OffsetBoxZ->SetVisibility(ESlateVisibility::Visible);
		WallWidget->DeleteButton->SetVisibility(ESlateVisibility::Visible);

		break;

	}
}

void AArcWizPlayerController::SpawnAndGenerateRoad(FVector Dimension_)
{
	FActorSpawnParameters Params;
	FRotator LookAtRotation;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (Road) Road->DeHighlightRoad();
	auto SpawnActor = GetWorld()->SpawnActor<ARoadGenerator>(ARoadGenerator::StaticClass(), StartLocation, FRotator::ZeroRotator, Params);
	if (Road = Cast<ARoadGenerator>(SpawnActor); Road) {
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "Valid Actor");
	}

	Road->GenerateRoad(Dimension_, FVector(0, 0, 0), Material);

	float angle = GetAngle(StartLocation, EndLocation);
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FString::FromInt(angle));

	LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	Road->SetActorRotation(LookAtRotation);
	Road->HighlightRoad();
}

float AArcWizPlayerController::GetAngle(FVector V1, FVector V2)
{
	FVector NormVector1 = V1.GetSafeNormal();
	FVector NormVector2 = V2.GetSafeNormal();

	float DotProduct = FVector::DotProduct(NormVector1, NormVector2);

	DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);

	float AngleRadians = FMath::Acos(DotProduct);

	float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);

	return AngleDegrees;
}

bool AArcWizPlayerController::OnRightOrleft(FVector FirstPoint, FVector SecondPoint, FVector Prev)
{
	FVector V1 = Prev - FirstPoint;
	FVector V2 = Prev - SecondPoint;
	FVector CrossProduct = FVector::CrossProduct(V1, V2);

	if (CrossProduct.Z > 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "Right");
		return false;
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "Left");
		return true;
	}
}

void AArcWizPlayerController::SnapActor(AActor* actor, float SnapValue)
{
	auto location = actor->GetActorLocation();
	location.X = FMath::RoundToFloat(location.X / SnapValue) * SnapValue;
	location.Y = FMath::RoundToFloat(location.Y / SnapValue) * SnapValue;
	actor->SetActorLocation(location);
}

void AArcWizPlayerController::WallMode()
{
	isMoving = true;

	DeSelectFunction();
	bAdjustMode = false;

	if (Roof) Roof->Destroy();

	HouseConstructionMode = EHouseConstructionMode::Wall;
	SetVisibility();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	if (LocalPlayer) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);

		if (Subsystem) {

			Subsystem->RemoveMappingContext(DoorMapping);
			Subsystem->RemoveMappingContext(RoadCreationMapping);
			Subsystem->AddMappingContext(WallGenerationMapping, 0);
		}
	}

	SpawnAndGenerate();

}

void AArcWizPlayerController::DoorMode()
{

	DeSelectFunction();

	bAdjustMode = false;
	if (Wall) Wall->Destroy();
	if (Roof) Roof->Destroy();
	HouseConstructionMode = EHouseConstructionMode::Door;
	SetVisibility();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	if (LocalPlayer) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);

		if (Subsystem) {
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DoorMapping, 0);
		}
	}
}

void AArcWizPlayerController::RoofMode()
{

	DeSelectFunction();

	bAdjustMode = false;

	if (Wall) Wall->Destroy();
	if (Roof) Roof->Destroy();

	isMoving = true;
	HouseConstructionMode = EHouseConstructionMode::Roof;
	SetVisibility();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	if (LocalPlayer) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);

		if (Subsystem) {

			Subsystem->RemoveMappingContext(DoorMapping);
			Subsystem->AddMappingContext(WallGenerationMapping, 0);
		}
	}

	SpawnAndGenerate();
}

void AArcWizPlayerController::ViewMode()
{
	DeSelectFunction();

	bAdjustMode = false;

	if (Wall) Wall->Destroy();
	if (Roof) Roof->Destroy();

	HouseConstructionMode = EHouseConstructionMode::View;
	SetVisibility();
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	if (LocalPlayer) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);

		if (Subsystem) {
			Subsystem->ClearAllMappings();
		}
	}

}

void AArcWizPlayerController::AdjustMode()
{
	DeSelectFunction();

	bAdjustMode = true;

	if (Wall) Wall->Destroy();
	if (Roof) Roof->Destroy();

	HouseConstructionMode = EHouseConstructionMode::Adjust;
	SetVisibility();
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	if (LocalPlayer) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);

		if (Subsystem) {
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(AdjustmentMapping, 0);
		}
	}

}

void AArcWizPlayerController::DeleteObject()
{
	if (Wall) Wall->Destroy();
	if (Roof) Roof->Destroy();
}

void AArcWizPlayerController::SpawnAndGenerate()
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (HouseConstructionMode == EHouseConstructionMode::Wall) {
		auto SpawnActor = GetWorld()->SpawnActor<AWallGenerator>(WallGeneratorClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);

		if (Wall = Cast<AWallGenerator>(SpawnActor); Wall) {
			Wall->GenerateWall(StaticCast<int32>(WallWidget->SegmentNumber->GetValue()));
		}
	}
	else if (HouseConstructionMode == EHouseConstructionMode::Roof) {
		auto SpawnActor = GetWorld()->SpawnActor<ARoofGenerator>(ARoofGenerator::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

		float x = WallWidget->Length->GetValue();;
		float y = WallWidget->Width->GetValue();
		float z = WallWidget->Height->GetValue();

		if (Roof = Cast<ARoofGenerator>(SpawnActor); Roof) {
			Roof->GenerateRoof(FVector(x,y,z), Material);
		}
	}
	
}

void AArcWizPlayerController::DoorGenerationFunction()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

	if (Wall) Wall->DeHighlightWall();
	if (HitResult.bBlockingHit)
	{
		AWallGenerator* WallActor = Cast<AWallGenerator>(HitResult.GetActor());
		if (WallActor) {
			WallWidget->DoorScrollBox->SetVisibility(ESlateVisibility::Visible);
			Wall = WallActor;
			isMoving = false;
			 SelectedMesh = Cast<UStaticMeshComponent>(HitResult.GetComponent());

			if (SelectedMesh) {
				//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Yes");
				Wall->SetWallSegment(SelectedMesh);
				Wall->HighlightWall();
				WallWidget->DoorScrollBox->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void AArcWizPlayerController::AdjustmentFunction()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

	DeSelectFunction();
 	if (HitResult.bBlockingHit)
	{
		if (auto SelectedActor = Cast<ARoofGenerator>(HitResult.GetActor()); SelectedActor) {

			Roof = SelectedActor;
			Roof->HighlightRoof();
			CurrentLocation = Roof->GetActorLocation();
			WallWidget->RoofLengthBox->SetVisibility(ESlateVisibility::Visible);
			WallWidget->RoofWidthBox->SetVisibility(ESlateVisibility::Visible);
			WallWidget->RoofHeightBox->SetVisibility(ESlateVisibility::Visible);
		}
		else if (auto SelectedActor1 = Cast<AWallGenerator>(HitResult.GetActor()); SelectedActor1) {

			Wall = SelectedActor1;
			Wall->HighlightWalls();
			CurrentLocation = Wall->GetActorLocation();
			WallWidget->RoofLengthBox->SetVisibility(ESlateVisibility::Collapsed);
			WallWidget->RoofWidthBox->SetVisibility(ESlateVisibility::Collapsed);
			WallWidget->RoofHeightBox->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void AArcWizPlayerController::DeSelectFunction()
{
	if (bAdjustMode) {
		if (Wall) {
			Wall->DeHighlightWall();
			Wall->DeHighlightWalls();
			Wall = nullptr;
		}

		if (Roof) {
			Roof->DeHighlightRoof();
			Roof = nullptr;
		}
	}
}

void AArcWizPlayerController::HandleSegmentChange(float segments)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Bind");

	if (Wall) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Valid Wall");

		Wall->GenerateWall(StaticCast<int32>(segments));
	}
}

void AArcWizPlayerController::HandleXOffsetChange(float Offset)
{
	if (Roof) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += Offset;
		loc.Y += WallWidget->YOffset->GetValue();
		loc.Z += WallWidget->ZOffset->GetValue();
		Roof->SetActorLocation(loc);
	}

	if (Wall) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += Offset;
		loc.Y += WallWidget->YOffset->GetValue();
		loc.Z += WallWidget->ZOffset->GetValue();
		Wall->SetActorLocation(loc);
	}
}

void AArcWizPlayerController::HandleYOffsetChange(float Offset)
{
	if (Roof) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += WallWidget->XOffset->GetValue();
		loc.Y += Offset;
		loc.Z += WallWidget->ZOffset->GetValue();
		Roof->SetActorLocation(loc);
	}

	if (Wall) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += WallWidget->XOffset->GetValue();
		loc.Y += Offset;
		loc.Z += WallWidget->ZOffset->GetValue();
		Wall->SetActorLocation(loc);
	}
}

void AArcWizPlayerController::HandleZOffsetChange(float Offset)
{
	if (Roof) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += WallWidget->XOffset->GetValue();
		loc.Y += WallWidget->YOffset->GetValue();
		loc.Z += Offset;
		Roof->SetActorLocation(loc);
	}

	if (Wall) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += WallWidget->XOffset->GetValue();
		loc.Y += WallWidget->YOffset->GetValue();
		loc.Z += Offset;
		Wall->SetActorLocation(loc);
	}
}

void AArcWizPlayerController::HandleLengthChange(float length)
{
	if (Roof) {
		float x = length;
		float y = WallWidget->Width->GetValue();
		float z = WallWidget->Height->GetValue();

		Roof->GenerateRoof({x,y,z},Material);
	}
}

void AArcWizPlayerController::HandleWidthChange(float width)
{
	if (Roof) {
		float x = WallWidget->Length->GetValue();
		float y = width;
		float z = WallWidget->Height->GetValue();

		Roof->GenerateRoof({ x,y,z },Material);
	}
}

void AArcWizPlayerController::HandleHeightChange(float height)
{
	if (Roof) {
		float x = WallWidget->Length->GetValue();
		float y = WallWidget->Width->GetValue();
		float z = height;

		Roof->GenerateRoof({ x,y,z },Material);
	}
}

void AArcWizPlayerController::HandleDoorSelect(const FDoorType& DoorData)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Inside Door");
	if (Wall) {
		auto WallSegment = Wall->GetWallSegment();
		if (WallSegment) {
			auto location = WallSegment->GetRelativeLocation();
			WallSegment->SetStaticMesh(DoorData.DoorMesh);
			WallSegment->SetRelativeRotation(FRotator(0, 90, 0));
			WallSegment->SetRelativeLocation(location + FVector(-1, 0, 0));
			WallSegment->SetWorldScale3D(FVector(0.2,1.005,1));
		}
		Wall->DeHighlightWall();
		Wall = nullptr;
	}
	WallWidget->DoorScrollBox->SetVisibility(ESlateVisibility::Collapsed);

}

void AArcWizPlayerController::OnConstructionModeClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "1");
	bEditMode = false;
	RoadWidget->OnConstructionModeClicked();
}

void AArcWizPlayerController::OnEditorModeClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "1");
	bEditMode = true;
	RoadWidget->OnEditorModeClicked();
}

void AArcWizPlayerController::OnWidthChanged(float width)
{

	if (width > 700) width = 700;
	if (Road)
		Road->SetActorScale3D(FVector(1, width / Dimension.Y, 1));
}

void AArcWizPlayerController::DeleteRoad()
{
	if (Road)
		Road->Destroy();
}

void AArcWizPlayerController::OnXChange(float value)
{
	FVector Location;
	if (Road && bEditMode) {
		//Location = Road->GetActorLocation();
		RoadWidget->Location.X = value;
		Road->SetActorLocation(RoadWidget->Location);
	}
}

void AArcWizPlayerController::OnYChange(float value)
{
	FVector Location;
	if (Road && bEditMode) {
		//Location = Road->GetActorLocation();
		RoadWidget->Location.Y = value;
		Road->SetActorLocation(RoadWidget->Location);
	}
}
