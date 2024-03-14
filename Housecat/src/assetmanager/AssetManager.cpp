#include <SDL_image.h>


#include "AssetManager.h"

#include "../logger/Logger.h"
 

AssetManager::AssetManager() {
	Logger::Lifecycle("AssetManager Constructor Called!");
}

AssetManager::~AssetManager() {
	ClearAssets();
	Logger::Lifecycle("AssetManager Destructor Called!");
}




//TEXTURES
SDL_Texture* AssetManager::GetTexture(const std::string& assetID) {
	return textures[assetID];
}

void AssetManager::AddTexture(SDL_Renderer* renderer, const std::string& assetID, const std::string& filePath) {
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		Logger::Error("Failed to Load Texture: " + std::string(SDL_GetError()));
		return;
	}
	if (!surface) {
		Logger::Error("Failed to Load Surface: " + std::string(SDL_GetError()));
		return;
	}

	textures.emplace(assetID, texture);
}




//FONTS
TTF_Font* AssetManager::GetFont(const std::string& assetID) {
	return fonts[assetID];
}

void AssetManager::AddFont(const std::string& assetID, const std::string& filePath, int fontSize) {
	TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
	if (!font) {
		Logger::Error("Failed to Load Font: " + std::string(TTF_GetError()));
		return;
	}
	fonts.emplace(assetID, font);
}





//SOUNDS
Mix_Music* AssetManager::GetMusic(const std::string& assetID) {
	return musics[assetID];
}

void AssetManager::AddMusic(const std::string& assetID, const std::string& filePath) {
	Mix_Music* music = Mix_LoadMUS(filePath.c_str());
	if (!music) {
		Logger::Error("Failed to Load Music: " + std::string(Mix_GetError()));
		return;
	}
	musics.emplace(assetID, music);
}

//SFX
Mix_Chunk* AssetManager::GetSFX(const std::string& assetID) {
	return sounds[assetID];
}

void AssetManager::AddSFX(const std::string& assetID, const std::string& filePath) {
	Mix_Chunk* sfx = Mix_LoadWAV(filePath.c_str());
	if (!sfx) {
		Logger::Error("Failed to Load SFX: " + std::string(Mix_GetError()));
		return;
	}
	sounds.emplace(assetID, sfx);
}





void AssetManager::ClearAssets() {
	for (auto texture : textures) {
		//makes sure to deallocate texture!
		SDL_DestroyTexture(texture.second);
	}
	//only clears map
	textures.clear();

	for (auto font : fonts) {
		TTF_CloseFont(font.second);
	}
	fonts.clear();

	for (auto music : musics) {
		Mix_FreeMusic(music.second);
	}

	for (auto sfx : sounds) {
		Mix_FreeChunk(sfx.second);
	}
}