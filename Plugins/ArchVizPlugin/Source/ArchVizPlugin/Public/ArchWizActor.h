// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArchWizActor.generated.h"

UCLASS()
class ARCHVIZPLUGIN_API AArchWizActor : public AActor
{
	GENERATED_BODY()


public:	
	AArchWizActor();

	APlayerController* Controller;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SnapActor(AActor* actor, float SnapValue);
};

