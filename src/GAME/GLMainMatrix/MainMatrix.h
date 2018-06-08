#ifndef MAINMATRIX_H
#define MAINMATRIX_H
#include<GL/glew.h>
#include<glm/ext.hpp>
#include<string>
#include<iostream>
class MainMatrix
{
    public:
        /** Default constructor */
        MainMatrix();
        /** Default destructor */
        ~MainMatrix();
    GLint m_camera_x=0;
    GLint m_camera_y=0;
    GLfloat m_angle=0.0f;
    GLfloat m_zoom=1.0f;

    glm::mat4 ortho=glm::ortho(-640.0f,640.0f,480.0f,-480.0f);

    glm::mat4 translation=glm::mat4{1.0f};
    glm::mat4 rotation=glm::mat4{1.0f};
    glm::mat4 scalation=glm::mat4{1.0f};

    glm::mat4 model=scalation*rotation*translation;

    void step();

    glm::mat4 MatrixTransform(int TransTX,int TransTY,float TransRA,float TransRX,float TransRY,float TransSZ);

    private:
};

#endif // MAINMATRIX_H
