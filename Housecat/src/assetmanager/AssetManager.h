#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <map>
#include <string>
#include <memory>

#include "../editor/utilities/SDLToolKit.h"

class AssetManager {
private:
	std::map<std::string, SDL_Texture*> textures;

	std::map<std::string, TTF_Font*> fonts;

	std::map<std::string, Mix_Music*> musics;
	std::map<std::string, Mix_Chunk*> sounds;

	//TODO
	//assets to manage

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

	//sounds
	Mix_Music* GetMusic(const std::string& assetID);
	void AddMusic(const std::string& assetID, const std::string& filePath);
	//SFX
	Mix_Chunk* GetSFX(const std::string& assetID);
	void AddSFX(const std::string& assetID, const std::string& filePath);

};

//ptr for Editor
typedef std::unique_ptr<AssetManager> AssetManagerPtr;