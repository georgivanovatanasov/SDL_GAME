#ifndef GAME_H
#define GAME_H
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <glm/ext.hpp>
#include <src/GAME/GLMainMatrix/MainMatrix.h>
#include <src/GAME/SHADER/ShaderManager.h>
#include <src/GAME/SHADER/PostProcessingScreen/PostProcessor.h>
#include <src/OBJECTS/BASEOBJECT/Object.h>
#include <src/SPRITE/Sprite.h>
#include <src/OBJECTS/PLAYER/Player.h>
#include <src/OBJECTS/WORLD/COLLIDER/Collider.h>
#include <src/GAME/SCENE/Scene.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include<omp.h>
#include<time.h>
class Game
{
    public:
        /** Default constructor */
        Game();
        /** Default destructor */
        ~Game();
    void init();
    void run();
    void render();
    void step();
    void handle_window_events();
    private:
    bool running=true;
    //Window
    SDL_Window* window=NULL;
    //Event Handler
    SDL_Event event;
    //Scene
    Scene* scene = NULL;
    //Camera
    int camera_x=0;
    int camera_y=0;
    void camera_coordinates();
    //Main Matrix
    MainMatrix* MMatrix=NULL;
    //Shader Manager
    ShaderManager* SManager=NULL;
    //Post Processor
    PostProcessor* PProcessor=NULL;
    //Buttons
    void manage_buttons();
    //Load Shaders
    GLuint LoadShader(const char *vertex_path, const char *fragment_path);
    std::string readFile(const char *filePath);
};
#endif // GAME_H
