#include <iostream>
#include <string>
#include <memory>

#include <GL\glew.h>
#include <SDL.h>

using std::cout;
using std::endl;
using std::string;

enum RetErrorCodes {
	SDL_INIT_FAIL,
	WINDOW_CREATION_FAIL,
	GL_CONTEXT_CREATION_FAIL,
	GLEW_INIT_FAIL
};

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to to initialize SDL: %s", SDL_GetError());
		return SDL_INIT_FAIL;
	}

	const string TITLE = "Ymir";
	const size_t DEFAULT_WIDTH = 1024;
	const size_t DEFAULT_HEIGHT = 720;

	SDL_Window *window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_OPENGL);

	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window: %s", SDL_GetError());
		return WINDOW_CREATION_FAIL;
	}

	SDL_GLContext ctx = SDL_GL_CreateContext(window);

	if (!ctx) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create OpenGL context: %s", SDL_GetError());
		return GL_CONTEXT_CREATION_FAIL;
	}

	GLenum ret = glewInit();
	if (GLEW_OK != ret) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to init GLEW: %s", glewGetErrorString(ret));
		return GLEW_INIT_FAIL;
	}

	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);

	SDL_Delay(3000);

	SDL_GL_DeleteContext(ctx);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}