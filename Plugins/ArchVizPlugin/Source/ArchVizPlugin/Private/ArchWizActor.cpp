// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchWizActor.h"

// Sets default values
AArchWizActor::AArchWizActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AArchWizActor::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();
	
}

void AArchWizActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArchWizActor::SnapActor(AActor* actor, float SnapValue)
{
	auto location = actor->GetActorLocation();
	location.X = FMath::RoundToFloat(location.X / SnapValue) * SnapValue;
	location.Y = FMath::RoundToFloat(location.Y / SnapValue) * SnapValue;
	actor->SetActorLocation(location);
}

