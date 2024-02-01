// Fill out your copyright notice in the Description page of Project Settings.


#include "VisionCircle.h"

#include "RTSVisionFunctionLibrary.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UVisionCircle::UVisionCircle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


bool UVisionCircle::CanSee(AActor* Other)
{
	return this->SphereComponent->IsOverlappingActor(Other);
}

TArray<FCanvasUVTri> UVisionCircle::CreateTriangles()
{
	FVector ActorLocation = this->GetOwner()->GetActorLocation();
	FVector2d ActorLocation2d = FVector2d(ActorLocation.X, ActorLocation.Y);
	TArray<FVector2d> Points = URTSVisionFunctionLibrary::CircleOfPoints(this->Radius, 32);
	Points = URTSVisionFunctionLibrary::OffsetPoints(Points, ActorLocation2d);
	Points = URTSVisionFunctionLibrary::ScaleVector2ds(Points);  // TODO(jesse) Eventually I'd like to to be a config value
	return URTSVisionFunctionLibrary::CanvasUVTris(Points);
}

// Called when the game starts
void UVisionCircle::BeginPlay()
{
	Super::BeginPlay();

	this->Radius = 100.0f;
	this->SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->SphereComponent->SetSphereRadius(this->Radius);
	this->SphereComponent->UpdateOverlaps();
}


// Called every frame
void UVisionCircle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
