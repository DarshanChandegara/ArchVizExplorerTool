// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcWizPlayerController.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include <Components/TextBlock.h>


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


	RotateActionR = NewObject<UInputAction>(this);
	RotateActionR->ValueType = EInputActionValueType::Boolean;
	WallGenerationMapping->MapKey(RotateActionR, EKeys::R);

	RotateActionE = NewObject<UInputAction>(this);
	RotateActionE->ValueType = EInputActionValueType::Boolean;
	WallGenerationMapping->MapKey(RotateActionE, EKeys::T);


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

	InteriorMapping = NewObject<UInputMappingContext>(this);

	InteriorLeftClickAction = NewObject<UInputAction>(this);
	InteriorLeftClickAction->ValueType = EInputActionValueType::Boolean;
	InteriorMapping->MapKey(InteriorLeftClickAction, EKeys::LeftMouseButton);

	InteriorMapping->MapKey(RotateActionE, EKeys::T);
	InteriorMapping->MapKey(RotateActionR, EKeys::R);


	MaterialMapping = NewObject<UInputMappingContext>(this);

	MaterialLeftClickAction = NewObject<UInputAction>(this);
	MaterialLeftClickAction->ValueType = EInputActionValueType::Boolean;
	MaterialMapping->MapKey(MaterialLeftClickAction, EKeys::LeftMouseButton);



	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
	if (EIC) {

		EIC->BindAction(RoadGenerateAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::RoadGenerateFucntion);
		EIC->BindAction(WallGenerateAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::SpawnAndGenerate);
		EIC->BindAction(RotateActionR, ETriggerEvent::Completed, this, &AArcWizPlayerController::RotateFunctionR);
		EIC->BindAction(RotateActionE, ETriggerEvent::Completed, this, &AArcWizPlayerController::RotateFunctionE);
		EIC->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::DoorGenerationFunction);
		EIC->BindAction(AdjustAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::AdjustmentFunction);
		EIC->BindAction(DeSelectAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::DeSelectFunction);
		EIC->BindAction(InteriorLeftClickAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::InteriorLeftClickFunction);
		EIC->BindAction(MaterialLeftClickAction, ETriggerEvent::Completed, this, &AArcWizPlayerController::MaterialSelection);


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

	if (MaterialWidgetClass) {
		MaterialWidget = CreateWidget<UMaterialWidget>(this, MaterialWidgetClass);
	}

	if (InteriorWidgetClass) {
		InteriorWidget = CreateWidget<UInteriorWidget>(this, InteriorWidgetClass);
	}
}

void AArcWizPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving) {
		if (IsValid(Wall)) {
			if (FVector StartLocation_, WorldDirection; DeprojectMousePositionToWorld(StartLocation_, WorldDirection))
			{
				FVector EndLocation_ = StartLocation_ + WorldDirection * 100000;

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


		if (IsValid(Roof)) {

			if (FVector StartLocation_, WorldDirection; DeprojectMousePositionToWorld(StartLocation_, WorldDirection))
			{
				FVector EndLocation_ = StartLocation_ + WorldDirection * 100000;

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
		
		if (IsValid(Floor)) {

			if (FVector StartLocation_, WorldDirection; DeprojectMousePositionToWorld(StartLocation_, WorldDirection))
			{
				FVector EndLocation_ = StartLocation_ + WorldDirection * 100000;

				FCollisionQueryParams Params;
				Params.bTraceComplex = true;
				Params.AddIgnoredActor(Floor);

				if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation_, EndLocation_,
					ECC_Visibility, Params))
				{
					FVector Location = HitResult.Location;
					//Location.Z += WallWidget->ZOffset->GetValue();
					Floor->SetActorLocation(Location);

					SnapActor(Floor, 20);
				}
			}
		}

		if (IsValid(Interior)) {

			if (FVector StartLocation_, WorldDirection; DeprojectMousePositionToWorld(StartLocation_, WorldDirection))
			{
				FVector EndLocation_ = StartLocation_ + WorldDirection * 100000;

				FCollisionQueryParams Params;
				Params.bTraceComplex = true;
				Params.AddIgnoredActor(Interior);

				if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation_, EndLocation_,
					ECC_Visibility, Params))
				{
					FVector Location = HitResult.Location;
					Interior->SetActorLocation(Location);

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
		CleanUp();
		bRoadMode = true;
		isMoving = false;

		HouseConstructionMode = EHouseConstructionMode::none;
		SetHouseModeVisibility();

		WallWidget->RemoveFromParent();
		MaterialWidget->RemoveFromParent();
		InteriorWidget->RemoveFromParent();
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

				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(RoadCreationMapping, 0);
			}
		}
	}
	break;

	case EMode::HouseMode:
	{
		CleanUp();
		if (IsValid(Road)) Road->DeHighlightRoad();
		HouseConstructionMode = EHouseConstructionMode::none;
		SetHouseModeVisibility();

		RoadWidget->RemoveFromParent();
		MaterialWidget->RemoveFromParent();
		InteriorWidget->RemoveFromParent();
		WallWidget->AddToViewport();

		if (WallWidget) {
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Valid");
			WallWidget->WallButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::WallMode);
			WallWidget->DoorButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::DoorMode);
			WallWidget->RoofButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::RoofMode);
			WallWidget->FloorButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::FloorMode);
			WallWidget->ViewButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::ViewMode);
			WallWidget->AdjustButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::AdjustMode);

			WallWidget->SegmentNumber->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleSegmentChange);

			WallWidget->Length->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleLengthChange);
			WallWidget->Width->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleWidthChange);
			WallWidget->Height->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleHeightChange);

			WallWidget->XOffset->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleXOffsetChange);
			WallWidget->YOffset->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleYOffsetChange);
			WallWidget->ZOffset->OnValueChanged.AddDynamic(this, &AArcWizPlayerController::HandleZOffsetChange);

			WallWidget->DeleteButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::DeleteObject);
			WallWidget->MoveButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::MoveObject);

			WallWidget->DoorScrollBox->OnDoorSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleDoorSelect);
			WallWidget->DeleteDoorButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::DeleteDoor);

		}
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
	break;

	case EMode::InteriorMode:
	{
		CleanUp();
		bInteriorMode = true;
		if (IsValid(Road)) Road->DeHighlightRoad();
		if (IsValid(Road) && bRoadMode) Road->Destroy();

		HouseConstructionMode = EHouseConstructionMode::none;
		SetHouseModeVisibility();

		WallWidget->RemoveFromParent();
		MaterialWidget->RemoveFromParent();
		RoadWidget->RemoveFromParent();
		InteriorWidget->AddToViewport();

		if (InteriorWidget) {
			InteriorWidget->ChairButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::ChairButtonClick);
			InteriorWidget->TableButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::TableButtonClick);
			InteriorWidget->SofaButton->OnClicked.AddDynamic(this, &AArcWizPlayerController::SofaButtonClick);
			InteriorWidget->WallInterior->OnClicked.AddDynamic(this , &AArcWizPlayerController::WallInteriorButtonClick);
			InteriorWidget->CeilInterior->OnClicked.AddDynamic(this , &AArcWizPlayerController::CeilInteriorButtonClick);
			InteriorWidget->ChairScrollBox->OnStaticMeshSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleStaticMeshSelect);
			InteriorWidget->TableScrollBox->OnStaticMeshSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleStaticMeshSelect);
			InteriorWidget->SofaScrollBox->OnStaticMeshSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleStaticMeshSelect);
			InteriorWidget->WallInteriorScrollBox->OnStaticMeshSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleStaticMeshSelect);
			InteriorWidget->ChairScrollBox->OnStaticMeshSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleStaticMeshSelect);
			InteriorWidget->TableScrollBox->OnStaticMeshSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleStaticMeshSelect);
			InteriorWidget->SofaScrollBox->OnStaticMeshSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleStaticMeshSelect);
			InteriorWidget->CeilInteriorScrollBox->OnStaticMeshSelectEvent.BindUObject(this, &AArcWizPlayerController::HandleStaticMeshSelect);
		}

		ULocalPlayer* LocalPlayer = GetLocalPlayer();
		check(LocalPlayer);

		if (LocalPlayer) {

			UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			check(Subsystem);

			if (Subsystem) {

				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(InteriorMapping, 0);
			}
		}
		SpawnAndGenerate();
	}
	break;

	case EMode::MaterialMode:
	{
		CleanUp();
		bMaterialMode = true;
		isMoving = false;
		if (IsValid(Road) && bRoadMode) Road->Destroy();

		HouseConstructionMode = EHouseConstructionMode::none;
		SetHouseModeVisibility();

		WallWidget->RemoveFromParent();
		RoadWidget->RemoveFromParent();
		InteriorWidget->RemoveFromParent();
		MaterialWidget->AddToViewport();


		if (MaterialWidget) {
			MaterialWidget->WallMaterialScrollBox->OnWallSelectedEvent.BindUObject(this, &AArcWizPlayerController::HandleWallMaterialSelect);
			MaterialWidget->RoadMaterialScrollBox->OnRoadSelectedEvent.BindUObject(this, &AArcWizPlayerController::HandleRoadMaterialSelect);
			MaterialWidget->PlayAnimation(MaterialWidget->PopUp);

		}

		ULocalPlayer* LocalPlayer = GetLocalPlayer();
		check(LocalPlayer);

		if (LocalPlayer) {

			UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			check(Subsystem);

			if (Subsystem) {

				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(MaterialMapping, 0);
			}
		}
	}
	break;
	}
}

void AArcWizPlayerController::SaveGame(FString Slotname)
{
	UArchVizSaveGame* SavedGameInstance = Cast<UArchVizSaveGame>(UGameplayStatics::CreateSaveGameObject(UArchVizSaveGame::StaticClass()));

	if (SavedGameInstance) {

		TArray<AActor*> AllActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld() , ARoadGenerator::StaticClass(), AllActors);

		for (auto actor : AllActors) {

			auto RoadActor = Cast<ARoadGenerator>(actor);
			if (RoadActor) {
				FRoadActorProperty RoadData;

				RoadData.RoadTransform = RoadActor->GetTransform();
				RoadData.Dimenstion = RoadActor->Size;
				RoadData.Material = RoadActor->Road->GetMaterial(0);
				SavedGameInstance->RoadActorArray.Add(RoadData);
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Saved Road");
			}
		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), WallGeneratorClass, AllActors);

		for (auto actor : AllActors) {

			auto WallActor = Cast<AWallGenerator>(actor);
			if (WallActor) {
				FWallActorProperty WallData;

				WallData.WallTransform = WallActor->GetActorTransform();

				for (UStaticMeshComponent* Mesh : WallActor->WallArray) {
					WallData.WallWarray.Add(Mesh->GetStaticMesh());
				}

				auto index = WallActor->WallArray[0]->GetMaterials().Num();


				switch (index) {
				case 1:
					WallData.Material = WallActor->WallArray[0]->GetMaterial(0);
					break;

				case 2:
					WallData.Material = WallActor->WallArray[0]->GetMaterial(1);
					break;

				case 3:
					WallData.Material = WallActor->WallArray[0]->GetMaterial(1);
					break;

				case 4:
					WallData.Material = WallActor->WallArray[0]->GetMaterial(3);
					break;

				}

				SavedGameInstance->WallActorArray.Add(WallData);
				
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Saved Wall");
			}
		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteriorGenerator::StaticClass(), AllActors);

		for (auto actor : AllActors) {

			auto InteriorActor = Cast<AInteriorGenerator>(actor);
			if (InteriorActor) {
				FInteriorActorProperty InteriorData;

				InteriorData.ActorTransform = InteriorActor->GetActorTransform();

				InteriorData.Mesh = InteriorActor->MeshComponent->GetStaticMesh();
				SavedGameInstance->InteriorActorArray.Add(InteriorData);

				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Saved Interior");
			}
		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoofGenerator::StaticClass(), AllActors);

		for (auto actor : AllActors) {

			auto RoofActor = Cast<ARoofGenerator>(actor);
			if (RoofActor) {
				FRoofActorProperty RoofData;

				RoofData.ActorTransform = RoofActor->GetActorTransform();
				RoofData.Dimension = RoofActor->Dimention;
				RoofData.ActorType = RoofActor->Actortype;
				if(RoofActor->Actortype == "Roof")
					RoofData.Material = RoofActor->Roof->GetMaterial(0);
				else 
					RoofData.Material = RoofActor->Floor->GetMaterial(0);

				SavedGameInstance->RoofActorArray.Add(RoofData);

				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Saved Roof");
			}
		}

		UGameplayStatics::SaveGameToSlot(SavedGameInstance, Slotname, 0);
	}
}

void AArcWizPlayerController::LoadGame(FString Slotname)
{
	UArchVizSaveGame* SavedGameInstance = Cast<UArchVizSaveGame>(UGameplayStatics::LoadGameFromSlot(Slotname,0));

	if (SavedGameInstance) {

		TArray<AActor*> AllActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoadGenerator::StaticClass(), AllActors);

		for (auto it : AllActors) it->Destroy();

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), WallGeneratorClass, AllActors);

		for (auto it : AllActors) it->Destroy();

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteriorGenerator::StaticClass(), AllActors);

		for (auto it : AllActors) it->Destroy();
		
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoofGenerator::StaticClass(), AllActors);

		for (auto it : AllActors) it->Destroy();

		for (auto it : SavedGameInstance->RoadActorArray) {
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Load Roads");
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			auto SpawnActor = GetWorld()->SpawnActor<ARoadGenerator>(ARoadGenerator::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

			SpawnActor->GenerateRoad(it.Dimenstion, {0,0,0} ,it.Material);
			SpawnActor->SetActorTransform(it.RoadTransform);

		}

		for (auto it : SavedGameInstance->WallActorArray) {
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Load Walls");
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			auto SpawnActor = GetWorld()->SpawnActor<AWallGenerator>(WallGeneratorClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);

			if (SpawnActor) {
				SpawnActor->SetActorTransform(it.WallTransform);
				SpawnActor->ClearWalls();

				for (int32 i = 0; i < it.WallWarray.Num(); i++) {

					UStaticMesh* Mesh = it.WallWarray[i];

					if (Mesh) {
						UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(SpawnActor);
						if (Mesh) {
							MeshComponent->SetStaticMesh(Mesh);
							MeshComponent->RegisterComponent();
							MeshComponent->AttachToComponent(SpawnActor->Scene, FAttachmentTransformRules::KeepRelativeTransform);

							if (MeshComponent->GetMaterials().Num() > 1) {
								MeshComponent->SetRelativeRotation(FRotator(0,90,0));
								MeshComponent->SetWorldScale3D(FVector(0.2, 1.005, 1));
								MeshComponent->SetRelativeLocation(FVector(i * 300, 0, 0) + FVector(-1, 0, 0));
							}
							else {
								MeshComponent->SetRelativeLocation(FVector(i * 300, 0, 0));
							}
							SpawnActor->WallArray.Add(MeshComponent);
							GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Mesh");

						}
					}
					SpawnActor->SetMaterial(it.Material);
				}
			}
		}

		for (auto it : SavedGameInstance->InteriorActorArray) {
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Load Interiors");
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			auto SpawnActor = GetWorld()->SpawnActor<AInteriorGenerator>(AInteriorGenerator::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

			SpawnActor->SetActorTransform(it.ActorTransform);
			SpawnActor->Generate(it.Mesh);
		}

		for (auto it : SavedGameInstance->RoofActorArray) {
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Load Roofs");
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			auto SpawnActor = GetWorld()->SpawnActor<ARoofGenerator>(ARoofGenerator::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

			SpawnActor->SetActorTransform(it.ActorTransform);
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, it.ActorType);

			if (it.ActorType == "Roof")
				SpawnActor->GenerateRoof(it.Dimension, it.Material, FVector(0, 0, 300));
			else if (it.ActorType == "Floor")
				SpawnActor->GenerateFloor(it.Dimension , it.Material);
		}
	}
}

TArray<FString>  AArcWizPlayerController::FindFiles(FString Path, FString Extension)
{
	TArray<FString> FileList;
	IFileManager& FileManager = IFileManager::Get();

	// Ensure the directory path is formatted correctly
	if (!Path.EndsWith("/"))
	{
		Path += "/";
	}

	// Build the full search path
	FString FullPath = Path + TEXT("*") + Extension;

	// Find the files
	FileManager.FindFiles(FileList, *FullPath, true, false);

	return FileList;
}

void AArcWizPlayerController::AddChilds(UScrollBox* ScrollBox, FString Text)
{
	if (ScrollBox)
	{
		Scroll = ScrollBox;
		UButton* Button = NewObject<UButton>(this);
		UTextBlock* TextBlock = NewObject<UTextBlock>(this);
		TextBlock->SetText(FText::FromString(Text));
		Button->AddChild(TextBlock);
		ScrollBox->AddChild(Button);
		
		//Button->SetContent();
		Button->OnClicked.AddDynamic(this , &AArcWizPlayerController::GetText);
	}
}

void AArcWizPlayerController::GetText()
{
	UButton* Button = Cast<UButton>(Scroll->GetAllChildren()[0]);

	if (Button) {
		UTextBlock* TextBlock = Cast<UTextBlock>(Button->GetAllChildren()[0]);
		if (TextBlock) {
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black,TextBlock->GetText().ToString());
		}
	}
}

void AArcWizPlayerController::CleanUp()
{
	if (IsValid(Wall)) {

		Wall->DeHighlightWalls();

		if (bWallMode) {
			Wall->Destroy();
		}
		else if (bMaterialMode) {
			Wall = nullptr;
		}
	}
	if (IsValid(Roof)) {

		Roof->DeHighlightRoof();
		if (bRoofMode) {
			Roof->Destroy();
		}
		else if (bMaterialMode) {
			Roof = nullptr;
		}
	}
	if (IsValid(Floor)) {

		Floor->DeHighlightRoof();

		if (bFloorMode) {
			Floor->Destroy();
		}
		else if (bMaterialMode) {
			Floor = nullptr;
		}
	}
	if (IsValid(Interior)) Interior->Destroy();

	if (IsValid(Road)) {
		Road->DeHighlightRoad();
	}

	bRoadMode = false;
	bMaterialMode = false;
	bInteriorMode = false;
}

void AArcWizPlayerController::SnapActor(AActor* actor, float SnapValue)
{
	auto location = actor->GetActorLocation();
	location.X = FMath::RoundToFloat(location.X / SnapValue) * SnapValue;
	location.Y = FMath::RoundToFloat(location.Y / SnapValue) * SnapValue;
	actor->SetActorLocation(location);
}

void AArcWizPlayerController::RotateFunctionE()
{
	if (IsValid(Wall)) {
		Wall->SetActorRelativeRotation(Wall->GetActorRotation() + FRotator(0, -90, 0));
	}

	if (IsValid(Roof)) {
		Roof->SetActorRelativeRotation(Roof->GetActorRotation() + FRotator(0, -90, 0));
	}
	
	if (IsValid(Floor)) {
		Floor->SetActorRelativeRotation(Floor->GetActorRotation() + FRotator(0, -90, 0));
	}

	if (IsValid(Interior)) {
		Interior->SetActorRelativeRotation(Interior->GetActorRotation() + FRotator(0, -30, 0));
	}
}

void AArcWizPlayerController::RotateFunctionR()
{
	if (IsValid(Wall)) {
		Wall->SetActorRelativeRotation(Wall->GetActorRotation() + FRotator(0, 90, 0));
	}

	if (IsValid(Roof)) {
		Roof->SetActorRelativeRotation(Roof->GetActorRotation() + FRotator(0, 90, 0));
	}

	if (IsValid(Floor)) {
		Floor->SetActorRelativeRotation(Floor->GetActorRotation() + FRotator(0, -90, 0));
	}
	
	if (IsValid(Interior)) {
		Interior->SetActorRelativeRotation(Interior->GetActorRotation() + FRotator(0, -90, 0));
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
			if (IsValid(Road)) Road->DeHighlightRoad();
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
	if (IsValid(Road))
		Road->DeHighlightRoad();

	if (bEditMode == false) {
		DoGenerate = false;
		SecondGeneration = false;
		StartLocation = FVector::ZeroVector;
		EndLocation = FVector::ZeroVector;
	}
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

void AArcWizPlayerController::OnConstructionModeClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "1");
	bEditMode = false;
	RoadWidget->OnConstructionModeClicked();
}

void AArcWizPlayerController::OnEditorModeClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "1");
	bEditMode = true;
	RoadWidget->OnEditorModeClicked();
}

void AArcWizPlayerController::OnWidthChanged(float width)
{

	if (width > 700) width = 700;
	if (IsValid(Road))
		Road->SetActorScale3D(FVector(1, width / Dimension.Y, 1));
}

void AArcWizPlayerController::DeleteRoad()
{
	if (IsValid(Road))
		Road->Destroy();
}

void AArcWizPlayerController::OnXChange(float value)
{
	FVector Location;
	if (IsValid(Road) && bEditMode) {
		//Location = Road->GetActorLocation();
		RoadWidget->Location.X = value;
		Road->SetActorLocation(RoadWidget->Location);
	}
}

void AArcWizPlayerController::OnYChange(float value)
{
	FVector Location;
	if (IsValid(Road) && bEditMode) {
		//Location = Road->GetActorLocation();
		RoadWidget->Location.Y = value;
		Road->SetActorLocation(RoadWidget->Location);
	}
}

void AArcWizPlayerController::SpawnAndGenerateRoad(FVector Dimension_)
{
	FActorSpawnParameters Params;
	FRotator LookAtRotation;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (IsValid(Road)) Road->DeHighlightRoad();
	auto SpawnActor = GetWorld()->SpawnActor<ARoadGenerator>(ARoadGenerator::StaticClass(), StartLocation, FRotator::ZeroRotator, Params);
	if (Road = Cast<ARoadGenerator>(SpawnActor); IsValid(Road)) {
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "Valid Actor");
	}

	Road->GenerateRoad(Dimension_, FVector(0, 0, 0), Material);

	float angle = GetAngle(StartLocation, EndLocation);
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FString::FromInt(angle));

	LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	Road->SetActorRotation(LookAtRotation);
	Road->HighlightRoad();
}

void AArcWizPlayerController::SetHouseModeVisibility()
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
	WallWidget->MoveButton->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->DeleteDoorButton->SetVisibility(ESlateVisibility::Collapsed);

	bWallMode = false;
	bRoofMode = false;
	bFloorMode = false;
	bDoorMode = false;
	bViewMode = false;
	bAdjustMode = false;
	bRoadMode = false;


	switch (HouseConstructionMode)
	{
	case EHouseConstructionMode::Wall:
		bWallMode = true;
		WallWidget->HorizontalBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EHouseConstructionMode::Roof:
		bRoofMode = true;
		WallWidget->RoofHeightBox->SetVisibility(ESlateVisibility::Visible);
		WallWidget->RoofLengthBox->SetVisibility(ESlateVisibility::Visible);
		WallWidget->RoofWidthBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EHouseConstructionMode::Door:
		bDoorMode = true;
		break;

	case EHouseConstructionMode::Floor:
		bFloorMode = true;
		WallWidget->RoofHeightBox->SetVisibility(ESlateVisibility::Visible);
		WallWidget->RoofLengthBox->SetVisibility(ESlateVisibility::Visible);
		WallWidget->RoofWidthBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EHouseConstructionMode::View:
		bViewMode = true;
		break;

	case EHouseConstructionMode::Adjust:
		bAdjustMode = true;
		WallWidget->OffsetBoxX->SetVisibility(ESlateVisibility::Visible);
		WallWidget->OffsetBoxY->SetVisibility(ESlateVisibility::Visible);
		WallWidget->OffsetBoxZ->SetVisibility(ESlateVisibility::Visible);
		WallWidget->DeleteButton->SetVisibility(ESlateVisibility::Visible);

		break;

	case EHouseConstructionMode::none:
		break;

	}
}

void AArcWizPlayerController::SetInteriorModeVisibility()
{
	InteriorWidget->ChairScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	InteriorWidget->TableScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	InteriorWidget->SofaScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	InteriorWidget->WallInteriorScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	InteriorWidget->CeilInteriorScrollBox->SetVisibility(ESlateVisibility::Collapsed);

	switch (InteriorType) {
	case EInteriorType::Chair:
		InteriorWidget->ChairScrollBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EInteriorType::Table:
		InteriorWidget->TableScrollBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EInteriorType::Sofa:
		InteriorWidget->SofaScrollBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EInteriorType::WallInterior:
		InteriorWidget->WallInteriorScrollBox->SetVisibility(ESlateVisibility::Visible);
		break;

	case EInteriorType::CeilInterior:
		InteriorWidget->CeilInteriorScrollBox->SetVisibility(ESlateVisibility::Visible);
	}
}

void AArcWizPlayerController::WallMode()
{

	DeSelectFunction();
	if (IsValid(Wall) && bWallMode) Wall->Destroy();
	if (IsValid(Roof) && bRoofMode) Roof->Destroy();
	if (IsValid(Floor) && bFloorMode) Floor->Destroy();


	HouseConstructionMode = EHouseConstructionMode::Wall;
	SetHouseModeVisibility();

	isMoving = true;

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	if (LocalPlayer) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);

		if (Subsystem) {

			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(WallGenerationMapping, 0);
		}
	}

	SpawnAndGenerate();

}

void AArcWizPlayerController::DoorMode()
{

	DeSelectFunction();

	if (IsValid(Wall) && bWallMode) Wall->Destroy();
	if (IsValid(Roof) && bRoofMode) Roof->Destroy();
	if (IsValid(Floor) && bFloorMode) Floor->Destroy();

	HouseConstructionMode = EHouseConstructionMode::Door;
	SetHouseModeVisibility();
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


	if (IsValid(Wall) && bWallMode) Wall->Destroy();
	if (IsValid(Roof) && bRoofMode) Roof->Destroy();
	if (IsValid(Floor) && bFloorMode) Floor->Destroy();

	HouseConstructionMode = EHouseConstructionMode::Roof;
	SetHouseModeVisibility();
	isMoving = true;

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	if (LocalPlayer) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);

		if (Subsystem) {

			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(WallGenerationMapping, 0);
		}
	}

	SpawnAndGenerate();
}

void AArcWizPlayerController::FloorMode()
{
	DeSelectFunction();


	if (IsValid(Wall) && bWallMode) Wall->Destroy();
	if (IsValid(Roof) && bRoofMode) Roof->Destroy();
	if (IsValid(Floor) && bFloorMode) Floor->Destroy();

	HouseConstructionMode = EHouseConstructionMode::Floor;
	SetHouseModeVisibility();
	isMoving = true;

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	if (LocalPlayer) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);

		if (Subsystem) {

			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(WallGenerationMapping, 0);
		}
	}

	SpawnAndGenerate();
}

void AArcWizPlayerController::ViewMode()
{
	DeSelectFunction();

	if (IsValid(Wall) && bWallMode) Wall->Destroy();
	if (IsValid(Roof) && bRoofMode) Roof->Destroy();
	if (IsValid(Floor) && bFloorMode) Floor->Destroy();

	HouseConstructionMode = EHouseConstructionMode::View;
	SetHouseModeVisibility();
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

	WallWidget->PlayAnimation(WallWidget->PopUp);

	isMoving = false;
	if (IsValid(Wall) && bWallMode) Wall->Destroy();
	if (IsValid(Roof) && bRoofMode) Roof->Destroy();
	if (IsValid(Floor) && bFloorMode) Floor->Destroy();

	HouseConstructionMode = EHouseConstructionMode::Adjust;
	SetHouseModeVisibility();
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
	if (IsValid(Wall)) Wall->Destroy();
	if (IsValid(Roof)) Roof->Destroy();
	if (IsValid(Floor)) Floor->Destroy();

}

void AArcWizPlayerController::MoveObject()
{
	if (IsValid(Wall) || IsValid(Roof) || IsValid(Floor)) {
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Bind");
		isMoving = true;
	}
}

void AArcWizPlayerController::DeleteDoor()
{
	if (IsValid(Wall)) {
		auto WallSegment = Wall->GetWallSegment();
		auto location = WallSegment->GetRelativeLocation();
		if (IsValid(WallSegment)) {
			WallSegment->SetStaticMesh(Wall->WallMesh);
			WallSegment->SetRelativeRotation(FRotator(0, 0, 0));
			WallSegment->SetRelativeLocation(location);
			WallSegment->SetRelativeScale3D(FVector(1,1,1));
		}
		Wall->DeHighlightWall();
		Wall = nullptr;
	}
}

void AArcWizPlayerController::SpawnAndGenerate()
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (ModeType == EMode::HouseMode) {
		if (HouseConstructionMode == EHouseConstructionMode::Wall) {
			auto SpawnActor = GetWorld()->SpawnActor<AWallGenerator>(WallGeneratorClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);

			if (Wall = Cast<AWallGenerator>(SpawnActor); IsValid(Wall)) {
				Wall->GenerateWall(StaticCast<int32>(WallWidget->SegmentNumber->GetValue()));
			}
		}
		else if (HouseConstructionMode == EHouseConstructionMode::Roof) {
			auto SpawnActor = GetWorld()->SpawnActor<ARoofGenerator>(ARoofGenerator::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

			float x = WallWidget->Length->GetValue();;
			float y = WallWidget->Width->GetValue();
			float z = WallWidget->Height->GetValue();

			if (Roof = Cast<ARoofGenerator>(SpawnActor); IsValid(Roof)) {
				Roof->GenerateRoof(FVector(x, y, z), Material , FVector(0,0,300));
			}
		}
		else if(HouseConstructionMode == EHouseConstructionMode::Floor){
			auto SpawnActor = GetWorld()->SpawnActor<ARoofGenerator>(ARoofGenerator::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

			float x = WallWidget->Length->GetValue();;
			float y = WallWidget->Width->GetValue();
			float z = WallWidget->Height->GetValue();

			if (Floor = Cast<ARoofGenerator>(SpawnActor); IsValid(Floor)) {
				Floor->GenerateFloor(FVector(x, y, z), Material);
			}
		}
	}
	else if (ModeType == EMode::InteriorMode) {

		auto SpawnActor = GetWorld()->SpawnActor<AInteriorGenerator>(AInteriorGenerator::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

		isMoving = true;
		if (Interior = Cast<AInteriorGenerator>(SpawnActor); IsValid(Interior)) {
			Interior->Generate(StaticMesh);
		}


	}

}

void AArcWizPlayerController::DoorGenerationFunction()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

	if (IsValid(Wall)) Wall->DeHighlightWall();
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
				//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::FromInt(SelectedMesh->GetMaterials().Num()));

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

			if(HitResult.GetComponent()->GetName() == "Roof")
			{
				Roof = SelectedActor;
				Roof->HighlightRoof();
				CurrentLocation = Roof->GetActorLocation();
			}
			else {
				Floor = SelectedActor;
				Floor->HighlightRoof();
				CurrentLocation = Floor->GetActorLocation();
			}
			WallWidget->RoofLengthBox->SetVisibility(ESlateVisibility::Visible);
			WallWidget->RoofWidthBox->SetVisibility(ESlateVisibility::Visible);
			WallWidget->RoofHeightBox->SetVisibility(ESlateVisibility::Visible);
			WallWidget->MoveButton->SetVisibility(ESlateVisibility::Visible);

		}
		else if (auto SelectedActor1 = Cast<AWallGenerator>(HitResult.GetActor()); SelectedActor1) {

			Wall = SelectedActor1;
			Wall->HighlightWalls();
			CurrentLocation = Wall->GetActorLocation();
			WallWidget->RoofLengthBox->SetVisibility(ESlateVisibility::Collapsed);
			WallWidget->RoofWidthBox->SetVisibility(ESlateVisibility::Collapsed);
			WallWidget->RoofHeightBox->SetVisibility(ESlateVisibility::Collapsed);
			WallWidget->MoveButton->SetVisibility(ESlateVisibility::Visible);

		}
	}
}

void AArcWizPlayerController::DeSelectFunction()
{
	if (bAdjustMode) {
		if (IsValid(Wall)) {
			Wall->DeHighlightWall();
			Wall->DeHighlightWalls();
			Wall = nullptr;
		}

		if (IsValid(Roof)) {
			Roof->DeHighlightRoof();
			Roof = nullptr;
		}
		
		if (IsValid(Floor)) {
			Floor->DeHighlightRoof();
			Floor = nullptr;
		}
	}
	isMoving = false;
}

void AArcWizPlayerController::HandleSegmentChange(float segments)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Bind");

	if (IsValid(Wall)) {
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Valid Wall");

		Wall->GenerateWall(StaticCast<int32>(segments));
	}
}

void AArcWizPlayerController::HandleXOffsetChange(float Offset)
{
	if (IsValid(Roof)) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += Offset;
		loc.Y += WallWidget->YOffset->GetValue();
		loc.Z += WallWidget->ZOffset->GetValue();
		Roof->SetActorLocation(loc);
	}	
	
	if (IsValid(Floor)) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += Offset;
		loc.Y += WallWidget->YOffset->GetValue();
		loc.Z += WallWidget->ZOffset->GetValue();
		Floor->SetActorLocation(loc);
	}

	if (IsValid(Wall)) {
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
	if (IsValid(Roof)) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += WallWidget->XOffset->GetValue();
		loc.Y += Offset;
		loc.Z += WallWidget->ZOffset->GetValue();
		Roof->SetActorLocation(loc);
	}	
	
	if (IsValid(Floor)) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += WallWidget->XOffset->GetValue();
		loc.Y += Offset;
		loc.Z += WallWidget->ZOffset->GetValue();
		Floor->SetActorLocation(loc);
	}

	if (IsValid(Wall)) {
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
	if (IsValid(Roof)) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += WallWidget->XOffset->GetValue();
		loc.Y += WallWidget->YOffset->GetValue();
		loc.Z += Offset;
		Roof->SetActorLocation(loc);
	}
	
	
	if (IsValid(Floor)) {
		//auto location = Roof->GetActorLocation();
		auto loc = CurrentLocation;
		loc.X += WallWidget->XOffset->GetValue();
		loc.Y += WallWidget->YOffset->GetValue();
		loc.Z += Offset;
		Floor->SetActorLocation(loc);
	}

	if (IsValid(Wall)) {
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
	if (IsValid(Roof)) {
		float x = length;
		float y = WallWidget->Width->GetValue();
		float z = WallWidget->Height->GetValue();

		Roof->GenerateRoof({ x,y,z }, Material , FVector(0,0,300));
	}
	
	if (IsValid(Floor)) {
		float x = length;
		float y = WallWidget->Width->GetValue();
		float z = WallWidget->Height->GetValue();

		Floor->GenerateFloor({ x,y,z }, Material);
	}
}

void AArcWizPlayerController::HandleWidthChange(float width)
{
	if (IsValid(Roof)) {
		float x = WallWidget->Length->GetValue();
		float y = width;
		float z = WallWidget->Height->GetValue();

		Roof->GenerateRoof({ x,y,z }, Material, FVector(0, 0, 300));
	}
	
	if (IsValid(Floor)) {
		float x = WallWidget->Length->GetValue();
		float y = width;
		float z = WallWidget->Height->GetValue();

		Floor->GenerateFloor({ x,y,z }, Material);
	}
}

void AArcWizPlayerController::HandleHeightChange(float height)
{
	if (IsValid(Roof)) {
		float x = WallWidget->Length->GetValue();
		float y = WallWidget->Width->GetValue();
		float z = height;

		Roof->GenerateRoof({ x,y,z }, Material, FVector(0, 0, 300));
	}

	if (IsValid(Floor)) {
		float x = WallWidget->Length->GetValue();
		float y = WallWidget->Width->GetValue();
		float z = height;

		Floor->GenerateFloor({ x,y,z }, Material);
	}
}

void AArcWizPlayerController::HandleDoorSelect(const FDoorType& DoorData)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Inside Door");
	if (IsValid(Wall)) {
		auto WallSegment = Wall->GetWallSegment();
		//UMaterialInterface* material{};
		if (WallSegment) {
			auto location = WallSegment->GetRelativeLocation();
			auto index = WallSegment->GetMaterials().Num();
			//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green , FString::FromInt(index));


			switch (index) {
			case 1:
				DefaultMaterial = WallSegment->GetMaterial(0);
				break;

			case 2:
				DefaultMaterial = WallSegment->GetMaterial(1);
				break;

			case 3:
				DefaultMaterial = WallSegment->GetMaterial(1);
				break;

			case 4:
				DefaultMaterial = WallSegment->GetMaterial(3);
				break;

			}

			
			//Wall->SetMaterial(DefaultMaterial);
			WallSegment->SetStaticMesh(DoorData.DoorMesh);
			//Wall->SetMaterial(DefaultMaterial);
			WallSegment->SetRelativeRotation(FRotator(0, 90, 0));
			WallSegment->SetRelativeLocation(location + FVector(-1, 0, 0));
			WallSegment->SetWorldScale3D(FVector(0.2, 1.005, 1));

		}
		Wall->DeHighlightWall();
		Wall = nullptr;
	}
	WallWidget->DoorScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	WallWidget->DeleteDoorButton->SetVisibility(ESlateVisibility::Visible);

}

void AArcWizPlayerController::InteriorLeftClickFunction()
{
	if (FVector StartLocation_, WorldDirection; DeprojectMousePositionToWorld(StartLocation_, WorldDirection))
	{
		FVector EndLocation_ = StartLocation + WorldDirection * 100000;

		FCollisionQueryParams Params;
		Params.bTraceComplex = true;
		Params.AddIgnoredActor(Interior);

		if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation_, EndLocation_,
			ECC_Visibility, Params))
		{
			auto actor = HitResult.GetActor();

			if (Cast<AInteriorGenerator>(actor)) {
				Interior->Destroy();
				Interior = Cast<AInteriorGenerator>(actor);
			}
			else {

				switch (InteriorType) {
				case EInteriorType::WallInterior:
				{
					if (Cast<AWallGenerator>(actor)) {
						SpawnAndGenerate();
					}
				}
				break;
				case EInteriorType::CeilInterior:
				{
					if ((IsValid(actor) && HitResult.GetComponent()->GetName() == "Roof")) {
						SpawnAndGenerate();
					}
				}
				break;
				default:
					if (IsValid(actor) && (HitResult.GetComponent()->GetName() == "Roof" || HitResult.GetComponent()->GetName() == "Floor")) {
						SpawnAndGenerate();
					}
				}
			}
			
		}
	}

	
}

void AArcWizPlayerController::ChairButtonClick()
{
	InteriorType = EInteriorType::Chair;
	SetInteriorModeVisibility();
}

void AArcWizPlayerController::TableButtonClick()
{
	InteriorType = EInteriorType::Table;
	SetInteriorModeVisibility();
}

void AArcWizPlayerController::SofaButtonClick()
{
	InteriorType = EInteriorType::Sofa;
	SetInteriorModeVisibility();
}

void AArcWizPlayerController::WallInteriorButtonClick()
{
	InteriorType = EInteriorType::WallInterior;
	SetInteriorModeVisibility();
}

void AArcWizPlayerController::CeilInteriorButtonClick()
{
	InteriorType = EInteriorType::CeilInterior;
	SetInteriorModeVisibility();
}

void AArcWizPlayerController::HandleStaticMeshSelect(const FStaticMeshtype& MeshData)
{
	if (IsValid(Interior)) {
		Interior->SetStaticMesh(MeshData.StaticMesh);
	}
}

void AArcWizPlayerController::MaterialSelection()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, "Left Click");
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

	MaterialWidget->RoadMaterialScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	MaterialWidget->WallMaterialScrollBox->SetVisibility(ESlateVisibility::Collapsed);

	if (IsValid(Roof) && !bAdjustMode) Roof->DeHighlightRoof();
	if (IsValid(Floor) && !bAdjustMode) Floor->DeHighlightRoof();
	if (IsValid(Wall) && !bAdjustMode) Wall->DeHighlightWalls();
	if (IsValid(Road)) Road->DeHighlightRoad();

	DeSelectFunction();
	if (HitResult.bBlockingHit)
	{
		if (auto SelectedActor = Cast<ARoofGenerator>(HitResult.GetActor()); SelectedActor) {

			Roof = SelectedActor;
			SelectedActor->HighlightRoof();
			MaterialWidget->WallMaterialScrollBox->SetVisibility(ESlateVisibility::Visible);
		}
		else if (auto SelectedActor1 = Cast<AWallGenerator>(HitResult.GetActor()); SelectedActor1) {

			Wall = SelectedActor1;
			SelectedActor1->HighlightWalls();
			MaterialWidget->WallMaterialScrollBox->SetVisibility(ESlateVisibility::Visible);
		}
		else if (auto SelectedActor2 = Cast<ARoadGenerator>(HitResult.GetActor()); SelectedActor2) {
			Road = SelectedActor2;
			SelectedActor2->HighlightRoad();
			MaterialWidget->RoadMaterialScrollBox->SetVisibility(ESlateVisibility::Visible);

		}
	}
}

void AArcWizPlayerController::HandleWallMaterialSelect(const FWallMaterial& WallData)
{
	if (IsValid(Wall))
	{
		Wall->SetMaterial(WallData.Material);
		Wall->DeHighlightWalls();
		Wall = nullptr;
	}

	if (IsValid(Floor))
	{
		Floor->SetMaterial(WallData.Material);
		Floor->DeHighlightRoof();
		Floor = nullptr;
	}

	if (IsValid(Roof))
	{
		Roof->SetMaterial(WallData.Material);
		Roof->DeHighlightRoof();
		Roof = nullptr;
	}
}

void AArcWizPlayerController::HandleRoadMaterialSelect(const FRoadMaterial& RoadData)
{
	if (IsValid(Road)) Road->SetMaterial(RoadData.Material);
}


