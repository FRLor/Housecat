#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>

#include "ProjectManagement.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"

#include "../../components/TransformComponent.h"
#include "../../components/SpriteComponent.h"

ProjectManagement::ProjectManagement() {}
ProjectManagement::~ProjectManagement() {}

void ProjectManagement::OpenProject(sol::state& lua, const std::string& fileName, EditorRenderer& renderer, std::shared_ptr<Canvas>& canvas,
	const AssetManagerPtr& assetManager, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath,
	int& tileSize) {

	std::filesystem::path filePath = fileName;
	//map check
	if (filePath.extension() != ".lua") {
		return;
	}

	sol::load_result script = lua.load_file(fileName);

	if (!script.valid()) {
		sol::error error = script;
		std::string errorMessage = error.what();
		return;
	}

	lua.script_file(fileName);

	sol::table project = lua["project"];

	int numAssets = 0;
	int numMaps = 0;

	std::string mapFile = "";

	while (true) {
		sol::optional<sol::table> projectAssets = project["assets"][numAssets];
		if (projectAssets == sol::nullopt) {
			break;
		}

		sol::table assets = project["assets"][numAssets];
		std::string assetsID = assets["asset_id"];
		std::string filePath = assets["file_path"];

		assetID.push_back(assetsID);
		assetFilePath.push_back(filePath);

		assetManager->AddEditorTexture(renderer, std::move(assetsID), std::move(filePath));
		numAssets++;
	}

	while (true) {
		sol::optional<sol::table> projectMaps = project["maps"][numMaps];
		if (projectMaps == sol::nullopt) {
			break;
		}

		sol::table maps = project["maps"][numMaps];
		mapFile = maps["file_path"];
		numMaps++;
	}

	sol::optional<sol::table> luaCanvas = project["canvas"];
	if (luaCanvas != sol::nullopt) {
		int canvasWidth = project["canvas"]["canvas_width"];
		int canvasHeight = project["canvas"]["canvas_height"];
		tileSize = project["canvas"]["tile_size"];

		canvas->SetCanvasWidth(std::move(canvasWidth));
		canvas->SetCanvasHeight(std::move(canvasHeight));
	}
	mapManagement->LoadMap(assetManager, fileName);
}