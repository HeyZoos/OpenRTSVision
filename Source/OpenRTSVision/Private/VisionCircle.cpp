// Fill out your copyright notice in the Description page of Project Settings.


#include "VisionCircle.h"

#include "RTSVisionFunctionLibrary.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UVisionCircle::UVisionCircle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	this->Radius = 100.0f;
	this->Resolution = 32;
}


bool UVisionCircle::CanSee(AActor* Other)
{
	return this->SphereComponent->IsOverlappingActor(Other);
}

TArray<FCanvasUVTri> UVisionCircle::CreateTriangles(float Scaling, ECollisionChannel VisionCollisionChannel)
{
	FVector ActorLocation = this->GetOwner()->GetActorLocation();
	FVector2d ActorLocation2d = FVector2d(ActorLocation.X, ActorLocation.Y);
	TArray<FVector2d> Points = URTSVisionFunctionLibrary::CircleOfPoints(this->Radius, this->Resolution);
	Points = URTSVisionFunctionLibrary::OffsetPoints(Points, ActorLocation2d);
	Points = URTSVisionFunctionLibrary::PointsToTrianglesAroundCenter(Points, ActorLocation2d);
	Points = URTSVisionFunctionLibrary::ScaleVector2ds(Points, Scaling);
	return URTSVisionFunctionLibrary::CanvasUVTris(Points);
}

// Called when the game starts
void UVisionCircle::BeginPlay()
{
	Super::BeginPlay();

	this->SphereComponent = NewObject<USphereComponent>(this->GetOwner(), "VisionCircleCollider");
	this->SphereComponent->SetSphereRadius(this->Radius);
	this->SphereComponent->AttachToComponent(this->GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	this->SphereComponent->RegisterComponent();
}