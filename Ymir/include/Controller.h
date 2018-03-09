#pragma once
#include <SDL.h>
#include <Camera.h>

class Controller {
public:
	void MoveCamera(Camera& camera, const float& deltaTime);
	static Controller& CallController() {
		static Controller controller;
		return controller;
	}
private:
	Controller();
	Controller(const Controller& root) = delete;
	Controller& operator=(const Controller&) = delete;
};