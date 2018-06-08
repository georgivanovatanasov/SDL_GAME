#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include <src/GAME/SHADER/ShaderManager.h>
#include <src/GAME/GLMainMatrix/MainMatrix.h>
#include <glm/ext.hpp>

class PostProcessor
{
    public:
        PostProcessor(MainMatrix* MMatrix,ShaderManager* SManager);
        virtual ~PostProcessor();
    void draw();
    GLuint FramebufferName = 0;
	GLuint renderedTexture = 0;
    private:
    ShaderManager* m_SManager=NULL;
    MainMatrix* m_MMatrix=NULL;
    float points[8]={
    -640,480,  640,480,
    640,-480,    -640,-480
    };

    float texcoords[8]={
    0.0f,0.0f,              1.0f,0.0f,
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

};

#endif // POSTPROCESSOR_H
