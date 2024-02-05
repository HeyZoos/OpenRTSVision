// Fill out your copyright notice in the Description page of Project Settings.


#include "VisionManager.h"

#include "Engine/Canvas.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"

// Sets default values for this component's properties
UVisionManager::UVisionManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

bool UVisionManager::CanSeeWithAnyVisionComponents(AActor* Other)
{
	for (auto ActorVision : this->ActorVisions)
	{
		if (ActorVision->CanSee(Other))
		{
			return true;
		}
	}

	return false;
}


// Called when the game starts
void UVisionManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<UVisionBase*> ActorVisionsContainer;
	this->GetOwner()->GetComponents<UVisionBase>(ActorVisionsContainer);
	this->ActorVisions = ActorVisionsContainer;
}

void UVisionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->GlobalVisionManager == nullptr)
	{
		this->GlobalVisionManager = static_cast<AGlobalVisionManager*>(
			UGameplayStatics::GetActorOfClass(
				this->GetWorld(),
				AGlobalVisionManager::StaticClass()
			)
		);

		if (this->GlobalVisionManager == nullptr)
		{
			UE_LOG(
				LogTemp,
				Error,
				TEXT("Actor %s cannot find instance of GlobalVisionManager in the level"),
				*this->GetOwner()->GetName()
			);
			return;
		}
		else
		{
			this->GlobalVisionManager->RegisterVisionManager(this);
			this->PrimaryComponentTick.bCanEverTick = false;
		}
	}
}
