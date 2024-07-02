// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArchWizTemplateActor.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API AArchWizTemplateActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	USceneComponent* Scene;

	TArray<AActor*> ChildActors;
	
public:	
	AArchWizTemplateActor();

	void AddToChildActorArray(AActor* Actor);

	TArray<AActor*> GetChildActorArray();

	void SetUpChilds();

	void DestroyActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
