// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlobalVisionManager.generated.h"

class UVisionManager;

UCLASS()
class OPENRTSVISION_API AGlobalVisionManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGlobalVisionManager();

	void RegisterVisionManager(UVisionManager* VisionManager);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Vision")
	class UCanvasRenderTarget2D* FogCanvasRenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Vision")
	class UCanvasRenderTarget2D* MistCanvasRenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Vision")
	float Scaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Vision")
	TEnumAsByte<ECollisionChannel> VisionCollisionChannel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<UVisionManager*> VisionManagers;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
