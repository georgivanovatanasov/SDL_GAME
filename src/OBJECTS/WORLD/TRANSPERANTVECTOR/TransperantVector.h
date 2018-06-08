#ifndef TRANSPERANTVECTOR_H
#define TRANSPERANTVECTOR_H
#include <GL/glew.h>
#include <src/OBJECTS/BASEOBJECT/Object.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class TransperantVector : public Object
{
    public:
        /** Default constructor */
        TransperantVector(std::string name,int depth,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int start_x,int start_y,short start_w,short start_h);
        bool disappear=0;
        /** Default destructor */
        virtual ~TransperantVector();
    void draw() override;
    void init();

    std::vector<Sprite*> sampler_vector;
    std::vector<GLfloat> verticles_vector;
    std::vector<GLfloat> texcoords_vector;
    std::vector<GLint> index_vector;

    private:

    //locations

    GLint CoordinatesLocation=0;
    GLint TexCoordsLocation=0;
    GLint IndicesLocation=0;

    //vbo and vao
    GLuint points_vbo=0;
    GLuint texcoord_vbo=0;
    GLuint indices_vbo=0;
    GLuint vao=0;

    bool inited=0;

};

#endif // TRANSPERANTVECTOR_H
