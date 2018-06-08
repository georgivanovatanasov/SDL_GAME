#ifndef SPRITE_H
#define SPRITE_H
#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<string>
#include "src/SOIL2/SOIL2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <png.h>
class Sprite
{
    public:
        Sprite(std::string name,const char* location);
        ~Sprite();
        GLuint get_sprite() {return m_sprite;}
        std::string get_name() {return m_name;}
        int get_w() {return m_w;}
        int get_h() {return m_h;}
    protected:

    private:
    GLuint m_sprite;
    int m_w, m_h;
    std::string m_name;
};

#endif // SPRITE_H
