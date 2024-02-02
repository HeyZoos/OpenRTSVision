// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSVisionFunctionLibrary.h"

// (TArray<FVector>) -> (TArray<FCanvasUVTri>)
TArray<FCanvasUVTri> URTSVisionFunctionLibrary::CanvasUVTris(TArray<FVector2d> Points)
{
	// Make sure that points is divisible by 3 or throw an exception
	if (Points.Num() % 3 != 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Points must be divisible by 3"));
		return TArray<FCanvasUVTri>();
	}
		
	
	TArray<FCanvasUVTri> Triangles;

	for (int i = 0; i < Points.Num() - 2; i += 3)
	{
		FCanvasUVTri Tri;
		Tri.V0_Pos = Points[i];
		Tri.V1_Pos = Points[i + 1];
		Tri.V2_Pos = Points[i + 2];
		Tri.V0_Color = FLinearColor::White;
		Tri.V1_Color = FLinearColor::White;
		Tri.V2_Color = FLinearColor::White;
		Triangles.Add(Tri);
	}

	return Triangles;
}

// (float, int) -> (TArray<FVector2D>)
TArray<FVector2d> URTSVisionFunctionLibrary::CircleOfPoints(float Radius, int NumberOfPoints)
{
	TArray<FVector2d> Points;

	for (int i = 0; i < NumberOfPoints; i++)
	{
		float Angle = i * 2 * PI / NumberOfPoints;
		float X = Radius * cos(Angle);
		float Y = Radius * sin(Angle);
		Points.Add(FVector2d(X, Y));
	}

	return Points;
}

// (TArray<FVector2D>, FVector2D) -> (TArray<FVector2D>)
TArray<FVector2d> URTSVisionFunctionLibrary::OffsetPoints(TArray<FVector2d> Input, FVector2d Offset)
{
	TArray<FVector2d> Output;

	for (int i = 0; i < Input.Num(); i++)
	{
		Output.Add(Offset + Input[i]);
	}

	return Output;
}

// (float, float) -> (FVector2D)
FVector2d URTSVisionFunctionLibrary::ScaleVector2d(FVector2d Vector, float Scale)
{
	return Vector * Scale;
}

// (TArray<FVector2D>, float) -> (TArray<FVector2D>)
TArray<FVector2d> URTSVisionFunctionLibrary::ScaleVector2ds(TArray<FVector2d> Input, float Scale)
{
	TArray<FVector2d> Output;

	for (int i = 0; i < Input.Num(); i++)
	{
		Output.Add(ScaleVector2d(Input[i], Scale));
	}

	return Output;
}

// (TArray<FVector2D>, FVector2D) -> (TArray<FVector2D>)
TArray<FVector2d> URTSVisionFunctionLibrary::PointsToTrianglesAroundCenter(TArray<FVector2d> Input, FVector2d Center)
{
	TArray<FVector2d> Output;

	for (int i = 0; i < Input.Num(); i++)
	{
		Output.Add(Input[i]);
		Output.Add(Center);

		if (i + 1 < Input.Num())
		{
			Output.Add(Input[i + 1]);
		}

		else
		{
			// Handle the case for the last single element, if needed.
			// Add the first element again to close the shape:
			Output.Add(Input[0]);
		}
	}

	return Output;
}
