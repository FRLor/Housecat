#pragma once

#include <memory>

#include "../utilities/SDLToolKit.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"


class ImGuiRendering: public System {
private:
	int canvasWidth;
	int canvasHeight;
	int canvasPreviousWidth;
	int canvasPreviousHeight;

	int tileSize;
	int tilePrevSize;

	bool createdTiles;
	bool removedTiles;

	int gridX;
	int gridY;
	bool gridSnap;

	std::shared_ptr<class Canvas> canvas;
	std::shared_ptr<class ImGuiFunctions> imguiFunctions;
	std::shared_ptr<class Mouse> mouse;
	std::unique_ptr<class EditManager> editManager;

	const bool MouseOutOfBounds() const;

public:
	ImGuiRendering();
	~ImGuiRendering();

	void Update(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, const float& zoom, const float& dT);

	void RenderGrid(EditorRenderer& renderer, SDL_Rect& camera, const float& zoom);

	void CreateNewCanvas();

	void UpdateCanvas();

};