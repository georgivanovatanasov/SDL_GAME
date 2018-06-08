#ifndef TILE_H
#define TILE_H
#include <src/OBJECTS/BASEOBJECT/Object.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include<vector>
class Tile : public Object
{

    public:
        /** Default constructor */
        Tile(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,short depth,int startx,int starty,int tiles_x,int tiles_y,int start_w,int start_h);
        /** Default destructor */
        ~Tile();

    void draw() override;
    private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                /*DRAWING*/
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //tiles:
    int m_tiles_x;
    int m_tiles_y;
    //drawing buffer data
    float points[8]={
    m_x-m_w*m_tiles_x/2.0f,m_y-m_h*m_tiles_y/2.0f,    m_x+m_w*m_tiles_x/2.0f,m_y-m_h*m_tiles_y/2.0f,
    m_x+m_w*m_tiles_x/2.0f,m_y+m_h*m_tiles_y/2.0f,    m_x-m_w*m_tiles_x/2.0f,m_y+m_h*m_tiles_y/2.0f
    };

    float texcoords[8]={

    0,0,                            m_tiles_x,0,
    m_tiles_x,m_tiles_y,            0,m_tiles_y

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

#endif // GRID_H
