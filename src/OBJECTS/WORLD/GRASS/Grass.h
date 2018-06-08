#ifndef GRASS_H
#define GRASS_H
#include <GL/glew.h>
#include <src/GAME/SHADER/ShaderManager.h>
#include <src/OBJECTS/BASEOBJECT/Object.h>
#include <src/SPRITE/Sprite.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <random>
#include<cmath>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>

class GrassBindingObject;
#include <src/OBJECTS/WORLD/GRASS/GrassBindingObject.h>


class Grass : public Object
{



    public:
        Grass(int ID_GBO,std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int start_x,int start_y,int start_w,int start_h);
        void draw() override;
        void step() override;
        void handle_events(SDL_Event& event) override;
        ~Grass();
        void init();
        GrassBindingObject* Connection=NULL;
        bool disappear=0;
        int get_ID() {return m_ID_GBO;}
    private:
    int m_ID_GBO;
    bool inited=0;

    //buffer vectors

    std::vector<GLfloat> verticles_vector;
    std::vector<GLfloat> texcoords_vector;
    std::vector<GLint> index_vector;


    std::vector<glm::vec4> model0_stdvector;
    std::vector<glm::vec4> model1_stdvector;
    std::vector<glm::vec4> model2_stdvector;
    std::vector<glm::vec4> model3_stdvector;

    std::vector<glm::vec4> color_vector;
    //locations

    GLint CoordinatesLocation=0;
    GLint TexCoordsLocation=0;
    GLint IndicesLocation=0;

    GLint ModelLocation0 = 0;
    GLint ModelLocation1 = 0;
    GLint ModelLocation2 = 0;
    GLint ModelLocation3 = 0;

    GLint ColorLocation=0;
    //vbo and vao
    GLuint points_vbo=0;
    GLuint texcoord_vbo=0;
    GLuint indices_vbo=0;

    GLuint model_vbo0;
    GLuint model_vbo1;
    GLuint model_vbo2;
    GLuint model_vbo3;

    GLuint color_vbo=0;

    GLuint vao=0;



    float get_distance(float sx,float sy,float dx,float dy);

    int m_rotation_timer=0;
    bool m_side_switch=1;
    float m_angle=0.0f;
    int m_wind_angle=1;


};
#endif // GRASS_H
