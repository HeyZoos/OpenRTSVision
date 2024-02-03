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

	UKismetRenderingLibrary::ClearRenderTarget2D(this->GetWorld(), this->FogCanvasRenderTarget);
	UKismetRenderingLibrary::ClearRenderTarget2D(this->GetWorld(), this->MistCanvasRenderTarget);

	this->GlobalVisionManager = (AGlobalVisionManager*)
		UGameplayStatics::GetActorOfClass(this->GetWorld(), AGlobalVisionManager::StaticClass());
	this->GlobalVisionManager->RegisterVisionManager(this);
}


// Called every frame
void UVisionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
