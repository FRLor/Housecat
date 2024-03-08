#pragma once

#include <SDL.h>

#include <glm/glm.hpp>

#include <memory>

struct SDLToolkit {
private:
	float start = 0.0f;
	float end = 10.0f;
	//interpolation factor
	float t = 0.5f;
	//lerp
	float result = glm::mix(start, end, t);

public:
	struct Destroyer {
		void operator()(SDL_Window* window) const {
			SDL_DestroyWindow(window);
		}

		void operator()(SDL_Renderer* renderer) const {
			SDL_DestroyRenderer(renderer);
		}

		void operator()(SDL_Texture* texture) const {
			SDL_DestroyTexture(texture);
		}
	};
};

typedef std::unique_ptr<SDL_Window, SDLToolkit::Destroyer> EditorWindow;
typedef std::unique_ptr<SDL_Renderer, SDLToolkit::Destroyer> EditorRenderer;
typedef std::unique_ptr<SDL_Texture, SDLToolkit::Destroyer> EditorTextures;

