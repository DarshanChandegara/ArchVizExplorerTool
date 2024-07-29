// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <RoadGenerator.h>
#include <InputMappingContext.h>
#include "RoadWidget.h"
#include "WallGenerator.h"
#include "WallWidget.h"
#include "RoofGenerator.h"
#include "MaterialWidget.h"
#include "InteriorGenerator.h"
#include "InteriorWidget.h"
#include "ArchVizSaveGame.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include <Components/ScrollBox.h>
#include "CustomButton.h"
#include "MainWidget.h"
#include "ArchWizTemplateActor.h"
#include "TemplateWidget.h"
#include "ArcWizPlayerController.generated.h"

UENUM()
enum class EMode : int8 {
	RoadMode ,
	HouseMode ,
	InteriorMode ,
	MaterialMode ,
	TemplateMode ,
	View
};

UENUM()
enum class EHouseConstructionMode :int8 {
	Wall ,
	Roof ,
	Floor ,
	Door ,
	View ,
	Adjust,
	none
};

UENUM()
enum class EInteriorType :int8 {
	Chair , 
	Table , 
	Sofa ,
	Stair,
	WallInterior,
	CeilInterior

};

UCLASS()
class ARCHVIZPLUGIN_API AArcWizPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	// Variables 

	UPROPERTY()
	AArchWizTemplateActor* TemplateActor;
		
	UPROPERTY()
	UMaterialInterface* DefaultMaterial;

	bool bWallMode = false;
	bool bRoofMode = false;
	bool bFloorMode = false;
	bool bDoorMode = false;
	bool bViewMode = false;
	bool bAdjustMode = false;
	bool bRoadMode = false;
	bool bMaterialMode = false;
	bool bInteriorMode = false;
	bool bWallGenerating = false;
	bool bFloorGenerating = false;
	bool bNewActor = false;
	// Road Generation

	UPROPERTY()
	bool DoGenerate = false;

	bool SecondGeneration = false;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;

	UPROPERTY()
	FVector PrevLocation;

	UPROPERTY()
	FVector Dimension;



	// Road UI

	bool bEditMode = false;



	// Wall
	bool isMoving = false;

	UPROPERTY()
	UStaticMeshComponent* SelectedMesh;

	UPROPERTY()
	FVector SlabDimension;


	FVector CurrentLocation;
private:

	// Functions

	void SetHouseModeVisibility();

	void SetInteriorModeVisibility();

	void CleanUp();

	float CalculateAngleBetweenVectors(const FVector& Vector1, const FVector& Vector2);

	void TemplateLeftClickFunction();

	void SetRotation();
	// Road 

	void SpawnAndGenerateRoad(FVector Dimension);

	float GetAngle(FVector V1, FVector V2);

	bool OnRightOrleft(FVector FirstPoint, FVector SecondPoint, FVector Prev);

	// Road UI

	void BindRoadWidget();

	UFUNCTION()
	void OnConstructionModeClicked();

	UFUNCTION()
	void OnEditorModeClicked();

	UFUNCTION()
	void OnWidthChanged(float width);

	UFUNCTION()
	void DeleteRoad();

	UFUNCTION()
	void OnXChange(float value);

	UFUNCTION()
	void OnYChange(float value);

	UFUNCTION()
	void NewRoadGenerateFucntion();

	// House
	void SpawnAndGenerate();

	void DoorGenerationFunction();

	void AdjustmentFunction();

	void DeSelectFunction();

	void ExapandWall();

	void HandleWallExpand();

	void ExpandFloor();

	void HandleFloorExpand();

	// House UI

	void BindHouseWidget();

	UFUNCTION()
	void WallMode();

	UFUNCTION()
	void DoorMode();

	UFUNCTION()
	void RoofMode();
		
	UFUNCTION()
	void FloorMode();

	UFUNCTION()
	void ViewMode();

	UFUNCTION()
	void AdjustMode();

	UFUNCTION()
	void DeleteObject();	

	UFUNCTION()
	void MoveObject();

	UFUNCTION()
	void DeleteDoor();

	UFUNCTION()
	void HandleSegmentChange(float segments);

	UFUNCTION()
	void HandleXOffsetChange(float Offset);

	UFUNCTION()
	void HandleYOffsetChange(float Offset);

	UFUNCTION()
	void HandleZOffsetChange(float Offset);

	UFUNCTION()
	void HandleLengthChange(float Offset);

	UFUNCTION()
	void HandleWidthChange(float Offset);

	UFUNCTION()
	void HandleHeightChange(float Offset);

	UFUNCTION()
	void HandleDoorSelect(const FDoorType& DoorData);

	UFUNCTION()
	void HandleWallMaterialSelect(const FWallMaterial& WallData);

	UFUNCTION()
	void HandleRoadMaterialSelect(const FRoadMaterial& WallData);

	// Interior

	void InteriorLeftClickFunction();

	// Interior UI

	void BindInteriorWidget();

	UFUNCTION()
	void ChairButtonClick();

	UFUNCTION()
	void TableButtonClick();

	UFUNCTION()
	void StairButtonClick();

	UFUNCTION()
	void SofaButtonClick();

	UFUNCTION()
	void WallInteriorButtonClick();

	UFUNCTION()
	void CeilInteriorButtonClick();

	UFUNCTION()
	void HandleStaticMeshSelect(const FStaticMeshtype& MeshData);

	// Material

	void MaterialSelection();

	void BindMaterialWidget();

	// Template UI

	UFUNCTION()
	void TemplateDeleteButtonClick();

	UFUNCTION()
	void TempleteCompleteButtonClick();

	UFUNCTION()
	void Template1ButtonClick();

	UFUNCTION()
	void Template2ButtonClick();

	UFUNCTION()
	void Template3ButtonClick();


public:

	// Variables 

	// Road
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road")
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road")
	UMaterialInterface* Material;

	UPROPERTY()
	ARoadGenerator* Road;

	UPROPERTY()
	UInputMappingContext* RoadCreationMapping;

	UPROPERTY()
	UInputAction* RoadGenerateAction;

	// Road Ui

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<URoadWidget> RoadWidgetClass;

	UPROPERTY()
	URoadWidget* RoadWidget;

	// Wall 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWallGenerator> WallGeneratorClass;

	UPROPERTY()
	AWallGenerator* Wall;

	UPROPERTY()
	ARoofGenerator* Roof;

	UPROPERTY()
	ARoofGenerator* Floor;

	UPROPERTY()
	UInputMappingContext* WallGenerationMapping;

	UPROPERTY()
	UInputMappingContext* FloorGenerationMapping;

	UPROPERTY()
	UInputAction* FloorLeftClick;

	UPROPERTY()
	UInputMappingContext* AdjustmentMapping;

	UPROPERTY()
	UInputAction* AdjustAction;

	UPROPERTY()
	UInputAction* DeSelectAction;

	UPROPERTY()
	UInputAction* WallGenerateAction;

	UPROPERTY()
	UInputAction* RotateActionT;

	UPROPERTY()
	UInputAction* RotateActionR;

	UPROPERTY()
	UInputAction* DeleteAction;

	UPROPERTY()
	UInputMappingContext* DoorMapping;

	UPROPERTY()
	UInputAction* LeftClickAction;

	// Interior

	UPROPERTY()
	UInputMappingContext* InteriorMapping;

	UPROPERTY()
	UInputAction* InteriorLeftClickAction;

	// Wall UI

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TSubclassOf<UWallWidget> WallWidgetClass;

	UPROPERTY()
	UWallWidget* WallWidget;


	// Interior

	UPROPERTY()
	AInteriorGenerator* Interior;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	// Interior UI

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TSubclassOf<UInteriorWidget> InteriorWidgetClass;

	UPROPERTY()
	UInteriorWidget* InteriorWidget;



	// Materials 

	UPROPERTY()
	UInputMappingContext* MaterialMapping;

	UPROPERTY()
	UInputAction* MaterialLeftClickAction;

	// Material UI

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TSubclassOf<UMaterialWidget> MaterialWidgetClass;

	UPROPERTY()
	UMaterialWidget* MaterialWidget;

	

public:

	// Functions

	// Overrides
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Road 

	void RoadGenerateFucntion();
	
	// Wall

	void RotateFunctionR();
	void RotateFunctionT();

	// Mode Change

	UPROPERTY()
	TEnumAsByte<EMode> ModeType;

	UPROPERTY()
	TEnumAsByte<EHouseConstructionMode> HouseConstructionMode;

	UPROPERTY()
	TEnumAsByte<EInteriorType> InteriorType;

	UFUNCTION()
	void HandleSaveButtonclick();

	UFUNCTION()
	void HandleRenameButtonclick();

	UFUNCTION(BlueprintCallable)
	void HandleModeChange(FString mode, ESelectInfo::Type Type);

	UFUNCTION(BlueprintCallable)
	bool SaveGame(FString Sloatname = "Default");

	UFUNCTION(BlueprintCallable)
	bool LoadGame(FString Sloatname = "Default");

	UFUNCTION(BlueprintCallable)
	TArray<FString> FindFiles(FString Path , FString Extension);

	UFUNCTION()
	void AddDataToLoadMap(int32 Index , FString Name);

	UFUNCTION()
	void GetText(int32 Id);

	UFUNCTION(BlueprintImplementableEvent)
	void NotifyUser(const FString& Text);

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TSubclassOf<UMainWidget> MainWidegtclass;

	UPROPERTY(BlueprintReadWrite)
	UMainWidget* MainWidget;

	UPROPERTY()
	TMap<int32, FString> SavedGameMapping;

	UFUNCTION()
	void DeleteLoadGame(int32 data);

	UPROPERTY()
	FString ProjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTemplateWidget> TemplateWidgetclass;

	UPROPERTY(BlueprintReadWrite)
	UTemplateWidget* TemplateWidget;

	UPROPERTY()
	UInputAction* TemplateLeftClickAction;

	UPROPERTY()
	UInputMappingContext* TemplateMapping;
};
