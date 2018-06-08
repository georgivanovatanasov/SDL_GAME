#ifndef BUTTON_H
#define BUTTON_H
#include <src/OBJECTS/BASEOBJECT/Object.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
class Button : public Object
{
    public:
        Button(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int start_x,int start_y,short start_w,short start_h);
        /** Default destructor */
        ~Button();


    void handle_events(SDL_Event& event) override;
    void step() override;
    void draw() override;
    bool get_clicked();
    bool check_mouse_collision();
    private:
    //mouse coordinates and check if clicked
    int mouse_x;
    int mouse_y;
    bool m_clicked=false;
    ////////////////////////////////////////

    /*
    float points[8]={
    m_x-m_w/2.0f,m_y-m_h/2.0f,      m_x+m_w/2.0f,m_y-m_h/2.0f,
    m_x+m_w/2.0f,m_y+m_h/2.0f,      m_x-m_w/2.0f,m_y+m_h/2.0f
    };
    */

    float points[8]={
    640.0f+m_x*1.0f-m_w*1.0f/2.0f,480.0f+m_y*1.0f-m_h*1.0f/2.0f,      640.0f+m_x*1.0f+m_w*1.0f/2.0f,480.0f+m_y*1.0f-m_h*1.0f/2.0f,
    640.0f+m_x*1.0f+m_w*1.0f/2.0f,480.0f+m_y*1.0f+m_h*1.0f/2.0f,      640.0f+m_x*1.0f-m_w*1.0f/2.0f,480.0f+m_y*1.0f+m_h*1.0f/2.0f
    };

    float texcoords[8]={
    0.0f,0.0f,    1.0f,0.0f,
    1.0f,0.5f,    0.0f,0.5f

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

    //clipped area
    float m_cw=1.0f;
    float m_ch=1.0f;


};

#endif // BUTTON_H
