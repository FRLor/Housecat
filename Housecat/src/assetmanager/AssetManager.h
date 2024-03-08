#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <map>
#include <string>
#include <memory>

#include "../editor/utilities/SDLToolKit.h"

class AssetManager {
private:
	std::map<std::string, SDL_Texture*> textures;

	std::map<std::string, TTF_Font*> fonts;

	//TODO
	//assets to manage
	//sound

public:
	AssetManager();
	~AssetManager();

	//textures
	SDL_Texture* GetTexture(const std::string& assetID);
	void AddTexture(SDL_Renderer* renderer, const std::string& assetID, const std::string& filePath);
	void ClearAssets();

	//fonts
	TTF_Font* GetFont(const std::string& assetID);
	void AddFont(const std::string& assetID, const std::string& filePath, int fontSize);

};

//ptr for Editor
typedef std::unique_ptr<AssetManager> AssetManagerPtr;