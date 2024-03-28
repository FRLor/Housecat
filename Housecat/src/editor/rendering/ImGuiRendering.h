#pragma once

#include <memory>
#include <sol/sol.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include <imgui/imgui_impl_sdl2.h>

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
	bool gridShow;

	bool isExit;

	std::shared_ptr<class Canvas> canvas;
	std::shared_ptr<class ImGuiFunctions> imguiFunctions;
	std::shared_ptr<class Mouse> mouse;
	std::unique_ptr<class EditManager> editManager;

	sol::state lua;

	const bool MouseOutOfBounds() const;

	void SetExit(bool exit) {
		isExit = exit;
	}

public:
	ImGuiRendering();
	~ImGuiRendering();

	void Update(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event, const float& zoom, const float& dT);

	void RenderGrid(EditorRenderer& renderer, SDL_Rect& camera, const float& zoom);

	void CreateNewCanvas();

	void UpdateCanvas();

	inline const bool& GetExit() const {
		return isExit;
	}

};