#pragma once
#include <raylib.h>
#include "raylib_utils.h"

class PixelCamera
{
public:
	Vector2 offset;
	Vector2 position;
	float rotation;
	float zoom;

public:
	PixelCamera(int screenWidth, int screenHeight, float virtualRatio);
	~PixelCamera();

	void Update();

	void BeginWorldMode();
	void EndWorldMode();
	void DrawWorld();

	void SetClearColor(const Color& color);

private:
	int screenWidth;
	int screenHeight;
	float virtualRatio;

	Color clearColor;
	Camera2D screenSpaceCamera;
	Camera2D worldSpaceCamera;
	RenderTexture2D renderTexture;
};