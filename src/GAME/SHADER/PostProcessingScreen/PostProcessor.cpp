#include "PostProcessor.h"

PostProcessor::PostProcessor(MainMatrix* MMatrix,ShaderManager* SManager): m_SManager{SManager},m_MMatrix{MMatrix}
{
glGenFramebuffers(1, &FramebufferName);
glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

glGenTextures(1, &renderedTexture);

// "Bind" the newly created texture : all future texture functions will modify this texture
glBindTexture(GL_TEXTURE_2D, renderedTexture);

// Give an empty image to OpenGL ( the last "0" )
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1280, 960, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

// Poor filtering. Needed !
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

glBindFramebuffer(GL_FRAMEBUFFER, 0);

    CoordinatesLocation = glGetAttribLocation(m_SManager->PostProcessorShaderProgram,"inCoordinates");
    TexCoordsLocation = glGetAttribLocation(m_SManager->PostProcessorShaderProgram,"inTexCoords");
    IndicesLocation = glGetAttribLocation(m_SManager->PostProcessorShaderProgram,"inIndex");




    glGenBuffers(1,&points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
    glBufferData(GL_ARRAY_BUFFER,8*sizeof(float),points,GL_STREAM_DRAW);



    glGenBuffers(1,&texcoord_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,texcoord_vbo);
    glBufferData(GL_ARRAY_BUFFER,8*sizeof(float),texcoords,GL_STREAM_DRAW);

    glGenBuffers(1,&indices_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,indices_vbo);
    glBufferData(GL_ARRAY_BUFFER,8*sizeof(float),indices,GL_STREAM_DRAW);

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


}

PostProcessor::~PostProcessor()
{
    //dtor
}

void PostProcessor::draw()
{
    glUseProgram(m_SManager->PostProcessorShaderProgram);
    glBindVertexArray(vao);
    GLuint OrthoLocation=glGetUniformLocation(m_SManager->PostProcessorShaderProgram,"unOrthogonal");
    if (OrthoLocation==-1) {std::cout<<"unOrthogonal location not found \n";}
    glUniformMatrix4fv(OrthoLocation,1,GL_FALSE,glm::value_ptr(m_MMatrix->ortho));

    glm::mat4 rotation_scale=m_MMatrix->scalation*m_MMatrix->rotation;
    GLuint ModelLocation=glGetUniformLocation(m_SManager->PostProcessorShaderProgram,"unModel");
    if (ModelLocation==-1) {std::cout<<"unModel location not found \n";}
    glUniformMatrix4fv(ModelLocation,1,GL_FALSE,glm::value_ptr(rotation_scale));

    glm::vec2 frame=glm::vec2(1.0f,1.0f);
    GLuint FrameLocation=glGetUniformLocation(m_SManager->PostProcessorShaderProgram,"unFrame");
    if (FrameLocation==-1) {std::cout<<"unFrame location not found \n";}
    glUniform2fv(FrameLocation,1,glm::value_ptr(frame));

    glm::vec2 clips=glm::vec2(1.0f,1.0f);
    GLuint ClipsLocation=glGetUniformLocation(m_SManager->PostProcessorShaderProgram,"unClip");
    if (ClipsLocation==-1) {std::cout<<"unClip location not found \n";}
    glUniform2fv(ClipsLocation,1,glm::value_ptr(clips));

    glm::vec4 color=glm::vec4(1.0f,1.0f,1.0f,1.0f);
    GLuint ColorLocation=glGetUniformLocation(m_SManager->PostProcessorShaderProgram,"unColor");
    if (ColorLocation==-1) {std::cout<<"unColor location not found \n";}
    glUniform4fv(ColorLocation,1,glm::value_ptr(color));

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,renderedTexture);


    glDrawArrays(GL_QUADS,0,4);
    glBindVertexArray(0);


    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glUseProgram(0);

    glDisableVertexAttribArray(IndicesLocation);
    glDisableVertexAttribArray(TexCoordsLocation);
    glDisableVertexAttribArray(CoordinatesLocation);


}
