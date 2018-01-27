#include <iostream>
#include <SDL.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to to initialize SDL: %s", SDL_GetError());
		return -1;
	}



	SDL_Quit();
       
    return 0;
}