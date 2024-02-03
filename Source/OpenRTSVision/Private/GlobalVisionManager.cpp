// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalVisionManager.h"

#include "VisionManager.h"
#include "Engine/Canvas.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Tasks/Task.h"

// Sets default values
AGlobalVisionManager::AGlobalVisionManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Scaling = 4;
}

void AGlobalVisionManager::RegisterVisionManager(UVisionManager* VisionManager)
{
	VisionManagers.Add(VisionManager);
}

// Called when the game starts or when spawned
void AGlobalVisionManager::BeginPlay()
{
	Super::BeginPlay();

	UKismetRenderingLibrary::ClearRenderTarget2D(this->GetWorld(), this->FogCanvasRenderTarget);
	UKismetRenderingLibrary::ClearRenderTarget2D(this->GetWorld(), this->MistCanvasRenderTarget);
}

// Called every frame
void AGlobalVisionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UE::Tasks::TTask<TArray<FCanvasUVTri>>> Tasks;
	TArray<FCanvasUVTri> Triangles;

	for (auto VisionManager : this->VisionManagers)
	{
		for (auto ActorVision : VisionManager->ActorVisions)
		{
			Tasks.Add(
				UE::Tasks::Launch(
					UE_SOURCE_LOCATION,
					[ActorVision, this]()
					{
						return ActorVision->CreateTriangles(this->Scaling);
					})
			);
		}
	}

	UE::Tasks::Wait(Tasks);
	for (auto Task : Tasks)
	{
		Triangles.Append(Task.GetResult());
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
