#pragma once

#include <SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

#include "./utilities/SDLToolkit.h"

#include "../assetmanager/AssetManager.h"





class Editor {
private:
	//editor window
	static const int windowBar = 25;
	static const int windowEditorWidth = 1920;
	static const int windowEditorHeight = 1080 - windowBar;

	const int EDITOR_FPS = 144;
	const int EDITOR_MILLISECS_PER_FRAME = 1000 / EDITOR_FPS;

	//editor state
	bool isRunning;

	int millisecsPreviousFrame;

	float zoom;

	SDL_Rect mouseTile;

	SDL_Rect camera;

	EditorWindow editorWindow;
	EditorRenderer editorRenderer;

	//ImGui
	ImGuiContext* editorImGuiContext;

	//AssetManager ptr
	AssetManagerPtr assetManager;

	//TODO

	//events?

	void CameraController(SDL_Event& event);
	void KeyboardCameraController();
public:
	Editor();
	~Editor();

	void Initialize();
	void Run();
	//void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	bool IsRunning() const { return isRunning; }
	void SetRunning(bool running) { isRunning = running; }

	auto GetWindowID();

};

