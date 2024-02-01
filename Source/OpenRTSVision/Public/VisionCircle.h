// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisionBase.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "VisionCircle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPENRTSVISION_API UVisionCircle : public UVisionBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVisionCircle();

	/**
	 * The radius of the circle
	 */
	UPROPERTY()
	float Radius;
	
	/**
	 * The actual collision component used to detect if an actor is visible
	 */
	UPROPERTY()
	USphereComponent* SphereComponent;
	
	/**
	 * How many triangles that make up the circle
	 */
	UPROPERTY()
	int Resolution;

	virtual bool CanSee(AActor* Other) override;
	
	virtual TArray<FCanvasUVTri> CreateTriangles() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
