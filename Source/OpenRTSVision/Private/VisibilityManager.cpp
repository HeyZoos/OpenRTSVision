// Fill out your copyright notice in the Description page of Project Settings.


#include "VisibilityManager.h"
#include "VisionBase.h"

#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UVisibilityManager::UVisibilityManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	this->BoxColliderSize = 50.0f;
}


// Called when the game starts
void UVisibilityManager::BeginPlay()
{
	Super::BeginPlay();

	// Create collider for parent
	this->Collider = this->GetOwner()->CreateDefaultSubobject<UBoxComponent>("VisibilityManagerCollider");
	// Convert float to vector with all values the same
	FVector BoxColliderSizeVector = FVector(this->BoxColliderSize, this->BoxColliderSize, this->BoxColliderSize);
	this->Collider->SetBoxExtent(BoxColliderSizeVector);
}


// Called every frame
void UVisibilityManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->GetOwner()->SetActorHiddenInGame(true);

	TArray<AActor*> OverlappingActors;
	this->Collider->GetOverlappingActors(OverlappingActors, nullptr);
	
	if (OverlappingActors.IsEmpty())
	{
		return;
	}

	for ( AActor* Actor : OverlappingActors )
	{
		UVisionBase* OtherActorVision = Actor->GetComponentByClass<UVisionBase>();

		if (OtherActorVision == nullptr)
		{
			continue;
		}

		if (OtherActorVision->CanSee(this->GetOwner()))
		{
			this->GetOwner()->SetActorHiddenInGame(false);
			return;
		}
	}
}
