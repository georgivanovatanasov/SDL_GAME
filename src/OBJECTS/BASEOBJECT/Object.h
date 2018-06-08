#ifndef OBJECT_H
#define OBJECT_H
#include<string>
#include<iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <src/GAME/SHADER/ShaderManager.h>
#include <src/GAME/GLMainMatrix/MainMatrix.h>
#include <src/SPRITE/Sprite.h>
#include<vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/ext.hpp>
class Object
{
    public:
        Object(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,short depth,int startx,int starty,short startw,short starth);
        virtual ~Object();

    //main matrix pointer
    MainMatrix* m_MMatrix=NULL;
    //ShaderManager pointer
    ShaderManager* m_SManager=NULL;
    //player x and y;
    int m_player_x=0;
    int m_player_y=0;
    //Current Grid,Object Persistence
    void SetInitializeGrid(int grid_x,int grid_y);
    short m_grid_x=0;
    short m_grid_y=0;
    bool m_persistent=false;
    //coordinate getters
    int get_x() const {return m_x;}
    int get_y() const {return m_y;}
    int get_w() const {return m_w;}
    int get_h() const {return m_h;}
    int get_clip_w() const {return m_clip_w;}
    int get_clip_h() const {return m_clip_h;}
    //drawing parameters
    void set_w(int new_w) {m_x=new_w;}
    void set_h(int new_h) {m_y=new_h;}
    void set_clip_w(int new_w) {m_clip_w=new_w;}
    void set_clip_h(int new_h) {m_clip_h=new_h;}
    //draw function
    virtual void draw();
    //draw depth on screen
    float m_depth;

    //events
    virtual void handle_events(SDL_Event& event);
    //step
    virtual void step();

    protected:
        //coordinates
        int m_x;
        int m_y;
        //width, height
        short m_w;
        short m_h;
        //clip
        int m_clip_w=0;
        int m_clip_h=0;
        //name
        std::string m_name;
        //the sprite of the object
        Sprite* m_sprite=NULL;
        //the color of the object
        float m_R=1.0f;
        float m_G=1.0f;
        float m_B=1.0f;
        float m_Alpha=1.0f;

};

#endif // OBJECT_H
