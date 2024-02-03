// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "VisionBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class OPENRTSVISION_API UVisionBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UVisionBase();

	/**
	 * Determines if the actor can see the other actor.
	 * This is what actually determines if another actor is visible.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool CanSee(AActor* Other) PURE_VIRTUAL(UVisionBase::CanSee, return false;);

	/**
	 * Generates a list of triangles representing the vision of the actor. This is used by
	 * the vision manager to draw to the canvas.
	 */
	UFUNCTION(BlueprintCallable)
	virtual TArray<FCanvasUVTri> CreateTriangles(float Scaling) PURE_VIRTUAL(UVisionBase::CreateTriangles,
	                                                            return TArray<FCanvasUVTri>(););

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision")
	TArray<FCanvasUVTri> CanvasUVTris;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
