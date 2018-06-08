#include "TransperantVector.h"

TransperantVector::TransperantVector(std::string name,int depth,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int start_x,int start_y,short start_w,short start_h): Object(name,SManager,MMatrix,sprite,depth,start_x,start_y,start_w,start_h)
{

}

TransperantVector::~TransperantVector()
{
    //dtor
}

void TransperantVector::init()
{
    for (int i=0;i<verticles_vector.size();i++)
    {
        if (i%2==0) {verticles_vector[i]=verticles_vector[i]+m_x;} else {verticles_vector[i]=verticles_vector[i]+m_y;}
    }





    CoordinatesLocation = glGetAttribLocation(m_SManager->DefaultShaderProgram,"inCoordinates");
    TexCoordsLocation = glGetAttribLocation(m_SManager->DefaultShaderProgram,"inTexCoords");
    IndicesLocation = glGetAttribLocation(m_SManager->DefaultShaderProgram,"inIndex");




    glGenBuffers(1,&points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
    glBufferData(GL_ARRAY_BUFFER,verticles_vector.size()*sizeof(GLfloat),&verticles_vector[0],GL_STREAM_DRAW);

    glGenBuffers(1,&texcoord_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,texcoord_vbo);
    glBufferData(GL_ARRAY_BUFFER,texcoords_vector.size()*sizeof(GLfloat),&texcoords_vector[0],GL_STREAM_DRAW);

    glGenBuffers(1,&indices_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,indices_vbo);
    glBufferData(GL_ARRAY_BUFFER,index_vector.size()*sizeof(GLfloat),&index_vector[0],GL_STREAM_DRAW);

    if (CoordinatesLocation==-1) {std::cout<<"inCoordinates location not found \n";}
    if (TexCoordsLocation==-1) {std::cout<<"inTexCoords location not found \n";}
    if (IndicesLocation==-1) {std::cout<<"inIndex location not found \n";}


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
    glVertexAttribPointer(CoordinatesLocation,2,GL_FLOAT,GL_FALSE,0,NULL);

    glBindBuffer(GL_ARRAY_BUFFER,texcoord_vbo);
    glVertexAttribPointer(TexCoordsLocation,2,GL_FLOAT,GL_FALSE,0,NULL);

    glBindBuffer(GL_ARRAY_BUFFER,indices_vbo);
    glVertexAttribPointer(IndicesLocation,1,GL_INT,GL_FALSE,0,NULL);

    glEnableVertexAttribArray(CoordinatesLocation);
    glEnableVertexAttribArray(TexCoordsLocation);
    glEnableVertexAttribArray(IndicesLocation);
    inited=true;
}


void TransperantVector::draw()
{

    if (inited==true)
    {



    int points=(verticles_vector.size())/8;

    for (int i=0;i<points;i++)
    {
    glUseProgram(m_SManager->DefaultShaderProgram);
    glBindVertexArray(vao);




    GLuint OrthoLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unOrthogonal");
    if (OrthoLocation==-1) {std::cout<<"unOrthogonal location not found \n";}
    glUniformMatrix4fv(OrthoLocation,1,GL_FALSE,glm::value_ptr(m_MMatrix->ortho));

    GLuint ModelLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unModel");
    if (ModelLocation==-1) {std::cout<<"unModel location not found \n";}
    glUniformMatrix4fv(ModelLocation,1,GL_FALSE,glm::value_ptr(m_MMatrix->model));


    glm::vec2 frame=glm::vec2(0.0f,0.0f);
    GLuint FrameLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unFrame");
    if (FrameLocation==-1) {std::cout<<"unFrame location not found \n";}
    glUniform2fv(FrameLocation,1,glm::value_ptr(frame));

    glm::vec2 clips=glm::vec2(1.0f,1.0f);
    GLuint ClipsLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unClip");
    if (ClipsLocation==-1) {std::cout<<"unClip location not found \n";}
    glUniform2fv(ClipsLocation,1,glm::value_ptr(clips));


    if (disappear==0)
        {
        m_Alpha=1.0f;
        }

    else
        {
        m_Alpha=0.2f;
        }


    glm::vec4 color=glm::vec4(m_R,m_G,m_B,m_Alpha);
    GLuint ColorLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unColor");
    if (ColorLocation==-1) {std::cout<<"unColor location not found \n";}
    glUniform4fv(ColorLocation,1,glm::value_ptr(color));






    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,sampler_vector[i]->get_sprite());


    glDrawArrays(GL_QUADS,0+(i*4),4);
    glBindVertexArray(0);


    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);


    glUseProgram(0);
    }


    }
};
