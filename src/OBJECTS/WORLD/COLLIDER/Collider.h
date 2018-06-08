#ifndef COLLIDER_H
#define COLLIDER_H
#include <src/OBJECTS/BASEOBJECT/Object.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <string>
#include <cmath>
class Collider : public Object
{
    public:
        /** Default constructor */
        Collider(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int start_x,int start_y,short start_w,short start_h,short clip_w,short clip_h);
        /** Default destructor */
        ~Collider();

    void draw() override;
    protected:

    private:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                /*DRAWING*/
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //drawing buffer data
    float points[8]={
    m_x*1.0f,m_y*1.0f,                  (m_x+m_w)*1.0f,m_y*1.0f,
    (m_x+m_w)*1.0f,(m_y+m_h)*1.0f,      m_x*1.0f,(m_y+m_h)*1.0f
    };



    float texcoords[8]={
    0.0f,0.0f,    1.0f,0.0f,
    1.0f,1.0f,    0.0f,1.0f

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

#endif // COLLIDER_H
