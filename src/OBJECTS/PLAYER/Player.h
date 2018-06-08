#ifndef PLAYER_H
#define PLAYER_H
#include <src/GAME/SHADER/ShaderManager.h>
#include<src/OBJECTS/BASEOBJECT/Object.h>>
#include<src/OBJECTS/WORLD/COLLIDER/Collider.h>
#include<src/OBJECTS/WORLD/TRANSPERANT/Transperant.h>
#include<src/OBJECTS/WORLD/TRANSPERANTVECTOR/TransperantVector.h>
#include<src/OBJECTS/WORLD/GRASS/Grass.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_opengl.h>
#include<string>
#include<vector>
class Player : public Object
{
    public:




    //constructor / deconstructor
        Player(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int start_x,int start_y);
        ~Player();
    //grid walls and get grid
    int box_x_min;
    int box_x_max;
    int box_y_min;
    int box_y_max;
    //collider vector and collides bool and functions
    bool collision_check_collider(int f_x,int f_y);
    //check transperant object vector
    void collision_check_transperant();
    //check transperant vector object vector
    void collision_check_transperant_vector();
    //check grass object vector
    void collision_check_grass();
    //events and step
    void handle_events(SDL_Event& event) override;
    void step() override;
    //draw
    void draw() override;
    //collider vector
    std::vector<Collider*> m_collider_vector;
    //transperant vector
    std::vector<Transperant*> m_transperant_vector;
    //transperant vector
    std::vector<TransperantVector*> m_transperant_vector_vector;
    //grass vector
    std::vector<Grass*> m_grass_vector;
    //Scene Coordinates
    int scene_startx=0;
    int scene_starty=0;
    int scene_endx=0;
    int scene_endy=0;
    void GetSceneSize(int start_x,int start_y,int end_x,int end_y);
    void SetGetGrid();
    //textbox message
    std::string msg="";















    private:

    //prev values and timer used for walking animation
    int m_x_prev;
    int m_y_prev;
    int sprite_timer=0;

    //player move functions
    void f_move_left(bool set_me) {m_move_left=set_me;}
    void f_move_right(bool set_me) {m_move_right=set_me;}
    void f_move_up(bool set_me) {m_move_up=set_me;}
    void f_move_down(bool set_me) {m_move_down=set_me;}

    //speed and move directions
    int m_speed=5;
    bool m_move_left=false;
    bool m_move_right=false;
    bool m_move_up=false;
    bool m_move_down=false;



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                /*DRAWING*/
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //drawing buffer data
    float points[8]={
    -m_w*1.0f/2.0f,-m_h*1.0f/2.0f,  m_w*1.0f/2.0f,-m_h*1.0f/2.0f,
    m_w*1.0f/2.0f,m_h*1.0f/2.0f,    -m_w*1.0f/2.0f,m_h*1.0f/2.0f
    };

    float texcoords[8]={
    0.0f,0.0f,              1.0f/8.0f,0.0f,
    1.0f/8.0f,1.0f/8.0f,    0.0f,1.0f/8.0f

    };


    int indices[4]={
    0,  1,
    2,  3
    };

    //locations

    GLint CoordinatesLocation = 0;
    GLint TexCoordsLocation = 0;
    GLint IndicesLocation = 0;

    //vbo and vao
    GLuint points_vbo=0;
    GLuint texcoord_vbo=0;
    GLuint indices_vbo=0;
    GLuint vao = 0;

    //frames

    float m_fr_x=0.0f;
    float m_fr_y=0.0f;


};

#endif // PLAYER_H
