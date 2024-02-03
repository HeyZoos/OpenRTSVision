// Fill out your copyright notice in the Description page of Project Settings.


#include "VisionCone.h"

#include "RTSVisionFunctionLibrary.h"

// Sets default values for this component's properties
UVisionCone::UVisionCone()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	this->Radius = 200.0f;
	this->NumberOfTriangles = 32;
	this->ArcLengthInDegrees = 180.0f;
}

TArray<FCanvasUVTri> UVisionCone::CreateTriangles(float Scaling)
{
	TArray<FVector> Points;

	FVector ActorLocation = this->GetOwner()->GetActorLocation();
	FVector ActorForwardVector = this->GetOwner()->GetActorForwardVector();
	float Angle = this->ArcLengthInDegrees / this->NumberOfTriangles;

	// The `<=` is to make sure we get the last point
	for (int i = 0; i <= NumberOfTriangles; i++)
	{
		float RotateAngle = (i * Angle) - (ArcLengthInDegrees / 2);
		FVector Start = ActorLocation;
		FVector End = ActorForwardVector.RotateAngleAxis(RotateAngle, FVector(0, 0, 1)) * this->Radius;
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this->GetOwner());
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

		if (bHit)
		{
			Points.Add(HitResult.ImpactPoint);
		}

		else
		{
			Points.Add(End);
		}
	}

	FVector2d ActorLocation2d = FVector2d(ActorLocation.X, ActorLocation.Y);
	TArray<FVector2d> Points2d = URTSVisionFunctionLibrary::ConvertFVector3DsToFVector2Ds(Points);
	Points2d = URTSVisionFunctionLibrary::OffsetPoints(Points2d, ActorLocation2d);
	Points2d = URTSVisionFunctionLibrary::PointsToTrianglesAroundCenter(Points2d, ActorLocation2d);
	Points2d = URTSVisionFunctionLibrary::ScaleVector2ds(Points2d, Scaling);
	return URTSVisionFunctionLibrary::CanvasUVTris(Points2d);
}

bool UVisionCone::CanSee(AActor* Other)
{
	// Get the locations of this actor and the other actor
	FVector OwnerLocation = this->GetOwner()->GetActorLocation();
	FVector OtherLocation = Other->GetActorLocation();

	// Calculate the direction vector from this actor to the other actor
	FVector DirectionToOther = (OtherLocation - OwnerLocation).GetSafeNormal();

	// Get the forward vector of this actor
	FVector ForwardVector = this->GetOwner()->GetActorForwardVector();

	// Calculate the look-at rotation from this actor to the other actor
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(DirectionToOther).Rotator();

	// Calculate the rotation difference between this actor's forward vector and the look-at rotation
	FRotator RotationDifference = (LookAtRotation - this->GetOwner()->GetActorRotation()).GetNormalized();

	// Check if the absolute yaw of the rotation difference is within the vision arc length
	if (FMath::Abs(RotationDifference.Yaw) <= this->ArcLengthInDegrees / 2)
	{
		return true;
	}

	return false;
}


// Called when the game starts
void UVisionCone::BeginPlay()
{
	Super::BeginPlay();

	this->SphereComponent = NewObject<USphereComponent>(this->GetOwner(), TEXT("VisionCodeCollider"));
	this->SphereComponent->SetSphereRadius(this->Radius);
	this->SphereComponent->AttachToComponent(this->GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	this->SphereComponent->RegisterComponent();
}
