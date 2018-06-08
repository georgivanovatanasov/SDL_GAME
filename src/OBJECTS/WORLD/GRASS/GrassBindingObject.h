#ifndef GRASSBINDINGOBJECT_H
#define GRASSBINDINGOBJECT_H
#include <GL/glew.h>
#include <src/GAME/SHADER/ShaderManager.h>
#include <src/OBJECTS/BASEOBJECT/Object.h>
#include <src/SPRITE/Sprite.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <random>
#include <vector>


class Grass;

#include <src/OBJECTS/WORLD/GRASS/Grass.h>

class GrassBindingObject
{
    public:
        GrassBindingObject(int ID_GBO);
        ~GrassBindingObject();
    std::vector<Grass*> grass_vector;
    void step();
    void set_all_disappear();

    Grass* to_delete = NULL;

    int get_ID() {return m_ID_GBO;}
    private:
    int m_ID_GBO;
};

#endif // GRASSBINDINGOBJECT_H
