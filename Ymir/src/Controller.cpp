#include <Controller.h>

Controller::Controller() {
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Controller::MoveCamera(Camera& camera, const float& deltaTime) {
	// SDL Update
	SDL_PumpEvents();

	// handle Keyboard
	Uint8* keysArray = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
	if (keysArray[SDL_SCANCODE_A]) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keysArray[SDL_SCANCODE_D]) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (keysArray[SDL_SCANCODE_S]) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keysArray[SDL_SCANCODE_W]) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keysArray[SDL_SCANCODE_SPACE]) {
		camera.ProcessKeyboard(UP, deltaTime);
	}
	if (keysArray[SDL_SCANCODE_LSHIFT]) {
		camera.ProcessKeyboard(DOWN, deltaTime);
	}

	// handle mouse
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	float deltaX = x;
	float deltaY = y;
	camera.ProcessMouseMove(deltaX, deltaY);
}