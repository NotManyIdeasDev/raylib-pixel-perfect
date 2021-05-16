#include "pixel_camera.h"

PixelCamera::PixelCamera(int screenWidth, int screenHeight, float virtualRatio)
	: offset({ 0.0f, 0.0f }), position({0.0f, 0.0f}), rotation(0.0f), zoom(1.0f), screenWidth(screenWidth), screenHeight(screenHeight), virtualRatio(virtualRatio)
{
	clearColor = { 10, 10, 10, 255 };

	worldSpaceCamera = { 0 };
	worldSpaceCamera.zoom = 1;

	screenSpaceCamera = { 0 };
	screenSpaceCamera.zoom = 1;

	renderTexture = LoadRenderTexture((screenWidth / virtualRatio) + 2, (screenHeight / virtualRatio) + 2);
}

PixelCamera::~PixelCamera()
{
	UnloadRenderTexture(renderTexture);
}

void PixelCamera::BeginWorldMode()
{
	BeginTextureMode(renderTexture);
	BeginMode2D(worldSpaceCamera);
	ClearBackground(clearColor);
}

void PixelCamera::EndWorldMode()
{
	EndMode2D();
	EndTextureMode();
}

void PixelCamera::DrawWorld()
{
	BeginMode2D(screenSpaceCamera);

	DrawTexturePro(
		renderTexture.texture,
		{ 0, 0, (float)renderTexture.texture.width, (float)-renderTexture.texture.height },
		{ -virtualRatio, -virtualRatio, screenWidth + (virtualRatio * 2), screenHeight + (virtualRatio * 2) },
		{ 0.0f, 0.0f },
		0.0f,
		WHITE
	);

	EndMode2D();
}

void PixelCamera::SetClearColor(const Color& color)
{
	clearColor = color;
}

void PixelCamera::Update()
{
	screenSpaceCamera.offset = offset;
	screenSpaceCamera.target = position;
	screenSpaceCamera.rotation = rotation;
	screenSpaceCamera.zoom = zoom;

	worldSpaceCamera.target.x = (int)screenSpaceCamera.target.x;
	screenSpaceCamera.target.x -= worldSpaceCamera.target.x;
	screenSpaceCamera.target.x *= virtualRatio;

	worldSpaceCamera.target.y = (int)screenSpaceCamera.target.y;
	screenSpaceCamera.target.y -= worldSpaceCamera.target.y;
	screenSpaceCamera.target.y *= virtualRatio;

}
