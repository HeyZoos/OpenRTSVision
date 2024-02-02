
// blueprint function library

#pragma once

#include "CoreMinimal.h"

#include "RTSVisionFunctionLibrary.generated.h"

UCLASS()
class URTSVisionFunctionLibrary : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:

	// (TArray<FVector>) -> (TArray<FCanvasUVTri>)
	static TArray<FCanvasUVTri> CanvasUVTris(TArray<FVector2d> Points);

	// (float, int) -> (TArray<FVector2D>)
	static TArray<FVector2d> CircleOfPoints(float Radius = 100.0f, int NumberOfPoints = 32);

	// (TArray<FVector2D>, FVector2D) -> (TArray<FVector2D>)
	static TArray<FVector2d> OffsetPoints(TArray<FVector2d> Input, FVector2d Offset);

	// (FVector2D, float) -> (FVector2D)
	static FVector2d ScaleVector2d(FVector2d Vector, float Scale = 1.0f);
	
	// (TArray<FVector2D>, float) -> (TArray<FVector2D>)
	static TArray<FVector2d> ScaleVector2ds(TArray<FVector2d> Input, float Scale = 1.0f);

	// (TArray<FVector2D>, FVector2D) -> (TArray<FVector2D>)
	static TArray<FVector2d> PointsToTrianglesAroundCenter(TArray<FVector2d> Input, FVector2d Center);

	// (TArray<FVector3D>) -> (TArray<FVector2D>)
	static TArray<FVector2d> ConvertFVector3DsToFVector2Ds(TArray<FVector3d> Input);
};