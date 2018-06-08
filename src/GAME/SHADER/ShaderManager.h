#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
class ShaderManager
{
    public:
        ShaderManager();
        ~ShaderManager();
   GLuint LoadShader(const char *vertex_path, const char *fragment_path);
   std::string readFile(const char *filePath);

   void init();
   GLuint PostProcessorShaderProgram=0;
   GLuint DefaultShaderProgram=0;
   GLuint GrassShaderProgram=0;
};

#endif // SHADERMANAGER_H
