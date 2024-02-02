// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "VisionBase.h"
#include "VisionCone.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPENRTSVISION_API UVisionCone : public UVisionBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVisionCone();

	UPROPERTY()
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Vision")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Vision")
	float ArcLengthInDegrees;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Vision")
	int NumberOfTriangles;

	TArray<FCanvasUVTri> CreateTriangles() override;

	bool CanSee(AActor* Other) override; 
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
