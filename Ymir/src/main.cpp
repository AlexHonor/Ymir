/* 
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey 
	Contact: berserk323@yandex.ru
*/

#include <SDL.h>

#include <iostream>
#include <string>
#include <memory>

#include <VertexArrayBuffer.h>
#include <Shader.h>
#include <RegisterAttrib.h>


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
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Unable to to initialize SDL: %s",
                     SDL_GetError());
        return SDL_INIT_FAIL;
    }

    const string TITLE = "Ymir";
    const size_t DEFAULT_WIDTH = 1024;
    const size_t DEFAULT_HEIGHT = 720;

    SDL_Window *window = SDL_CreateWindow(TITLE.c_str(),
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          DEFAULT_WIDTH,
                                          DEFAULT_HEIGHT,
                                          SDL_WINDOW_OPENGL);

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Failed to create window: %s",
                     SDL_GetError());
        return WINDOW_CREATION_FAIL;
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(window);

    if (!ctx) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Failed to create OpenGL context: %s",
                     SDL_GetError());
        return GL_CONTEXT_CREATION_FAIL;
    }

    GLenum ret = glewInit();
    if (GLEW_OK != ret) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Failed to init GLEW: %s",
                     glewGetErrorString(ret));
        return GLEW_INIT_FAIL;
    }

    bool loop_active = true;


	// Testing VAOs, VBOs, EBOs

	float dataUpperTriangle[] =
	{   // position        color
		-0.5f, -0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,  0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
	};

	float dataCoordLowerSquare[] =
	{ // position
		-0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
		0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 1.0f, 0.0f, 1.0f
	};


	unsigned int indices[] = {
		0, 1, 2,
		0, 3, 2
	};


	/* TEST */

	
	// Filling awesome table
	//													Имя	    Тип	Сколько Нормал СлотVAO
	RegisterAttrib::AttribTypeTable().AddAttribute("pos", GL_FLOAT, 2, GL_FALSE, 0);
	RegisterAttrib::AttribTypeTable().AddAttribute("color", GL_FLOAT, 3, GL_FALSE, 3);

	Layout layout;
	layout.Push(RegisterAttrib::AttribTypeTable().GetAttribute("pos"));
	layout.Push(RegisterAttrib::AttribTypeTable().GetAttribute("color"));

	VertexBuffer uppertriangleVBO(dataUpperTriangle, sizeof(dataUpperTriangle));
	VertexArray uppertriangleVAO;
	uppertriangleVAO.AddAttributes(uppertriangleVBO, layout);





	std::unordered_map<GLenum, std::string> shaders;
	shaders[GL_VERTEX_SHADER] = std::string("shaders/vertex.glsl");
	shaders[GL_FRAGMENT_SHADER] = std::string("shaders/fragment.glsl");
	Shader shader(shaders);
	shader.RunShader();

    while (loop_active) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    loop_active = false;
                break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        loop_active = false;
                    }
                break;
            }
        }

        glClearColor(0, 0.5, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		uppertriangleVAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

        SDL_GL_SwapWindow(window);
    }


    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
