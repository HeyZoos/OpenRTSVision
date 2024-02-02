// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisionBase.h"
#include "Components/ActorComponent.h"
#include "VisionManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPENRTSVISION_API UVisionManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVisionManager();

	UFUNCTION()
	bool CanSee(AActor* Other);

	UPROPERTY()
	class UCanvasRenderTarget2D* FogCanvasRenderTarget;
	
	UPROPERTY()
	class UCanvasRenderTarget2D* MistCanvasRenderTarget;

	UPROPERTY()
	TArray<UVisionBase*> ActorVisions;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
