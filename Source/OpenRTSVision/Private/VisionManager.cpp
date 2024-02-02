// Fill out your copyright notice in the Description page of Project Settings.


#include "VisionManager.h"

#include "Engine/Canvas.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"

// Sets default values for this component's properties
UVisionManager::UVisionManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

bool UVisionManager::CanSee(AActor* Other)
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
}


// Called every frame
void UVisionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<FCanvasUVTri> Triangles;

	for (auto ActorVision : this->ActorVisions)
	{
		// TODO(jesse) This could be parallelized
		TArray<FCanvasUVTri> ActorVisionTriangles = ActorVision->CreateTriangles();
		Triangles.Append(ActorVisionTriangles);
	}

	{
		UKismetRenderingLibrary::ClearRenderTarget2D(this->GetWorld(), this->MistCanvasRenderTarget);
		UCanvas* Canvas = nullptr;
		FDrawToRenderTargetContext Context;
		FVector2d Size = FVector2d(this->MistCanvasRenderTarget->SizeX, this->MistCanvasRenderTarget->SizeY);
		UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(
			this->GetWorld(),
			this->MistCanvasRenderTarget,
			Canvas,
			Size,
			Context
		);


		Canvas->K2_DrawTriangle(
			nullptr,
			Triangles
		);

		UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(
			this->GetWorld(),
			Context
		);
	}

	{
		UCanvas* Canvas = nullptr;
		FDrawToRenderTargetContext Context;
		FVector2d Size = FVector2d(this->FogCanvasRenderTarget->SizeX, this->FogCanvasRenderTarget->SizeY);
		UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(
			this->GetWorld(),
			this->FogCanvasRenderTarget,
			Canvas,
			Size,
			Context
		);


		Canvas->K2_DrawTriangle(
			nullptr,
			Triangles
		);

		UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(
			this->GetWorld(),
			Context
		);
	}
}
