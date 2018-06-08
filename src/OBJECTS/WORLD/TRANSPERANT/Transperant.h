#ifndef TRANSPERANT_H
#define TRANSPERANT_H
#include <GL/glew.h>
#include <src/OBJECTS/BASEOBJECT/Object.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
class Transperant : public Object
{
    public:
        /** Default constructor */
        Transperant(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int start_x,int start_y,short start_w,short start_h,short clip_w,short clip_h);
        bool disappear=0;
        /** Default destructor */
        virtual ~Transperant();
    void draw() override;

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

#endif // TRANSPERANT_H
