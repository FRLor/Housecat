#pragma once

#include <memory>

class ImGuiRendering {
private:
	int canvasWidth;
	int canvasHeight;
	int canvasPreviousWidth;
	int canvasPreviousHeight;

	int tileSize;

	int gridX;
	int gridY;

	std::shared_ptr<class Canvas> canvas;

public:
	ImGuiRendering();
	~ImGuiRendering();

	void Update(SDL_Renderer& renderer);

	void RenderGrid(SDL_Renderer& renderer);

	void CreateNewCanvas();

	void UpdateCanvas();

};