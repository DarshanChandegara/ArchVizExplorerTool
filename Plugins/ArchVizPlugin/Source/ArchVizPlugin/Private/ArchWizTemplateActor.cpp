// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchWizTemplateActor.h"

AArchWizTemplateActor::AArchWizTemplateActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
}

void AArchWizTemplateActor::AddToChildActorArray(AActor* Actor)
{
	ChildActors.Add(Actor);
}

TArray<AActor*> AArchWizTemplateActor::GetChildActorArray()
{
	return ChildActors;
}

void AArchWizTemplateActor::SetUpChilds()
{
	for (auto it : ChildActors) {
		it->AttachToActor(this , FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void AArchWizTemplateActor::DestroyActor()
{
	for (auto it : ChildActors) {
		it->Destroy();
	}
}

void AArchWizTemplateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArchWizTemplateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

