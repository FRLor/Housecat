#pragma once

#include <string>
#include <memory>
#include <sol/sol.hpp>
#include <filesystem>

#include "SDLToolkit.h"

#include "../../assetmanager/AssetManager.h"
#include "../rendering/Canvas.h"

class MapManagement {
public:
	MapManagement() = default;
	~MapManagement() = default;

	void LoadMap(const AssetManagerPtr& assetManager, const std::string& fileName);

	void SaveMap(std::filesystem::path fileName);

};