#include "MainMatrix.h"

MainMatrix::MainMatrix()
{
    //ctor
}

MainMatrix::~MainMatrix()
{
    //dtor
}

void MainMatrix::step()
{
    //identity
    translation=glm::mat4{1.0f};

    rotation=glm::mat4{1.0f};

    scalation=glm::mat4{1.0f};

    //transformations
    translation=glm::translate(glm::mat4{1.0f},glm::vec3{-m_camera_x-640,-m_camera_y-480,0.0f});

    rotation=glm::translate(rotation, glm::vec3(0.5f, 0.5f, 0.0f));
    rotation=glm::rotate(glm::mat4{1.0f},m_angle*1.0f/57.29578f,glm::vec3{0.0f,0.0f,1.0f});
    rotation=glm::translate(rotation, glm::vec3(-0.5f, -0.5f, 0.0f));

    scalation=glm::scale(glm::mat4{1.0f},glm::vec3(m_zoom,m_zoom,0.0f));

    //model matrix
    model=scalation*rotation*translation;
}


glm::mat4 MainMatrix::MatrixTransform(int TransTX,int TransTY,float TransRA,float TransRX,float TransRY,float TransSZ)
{

    //identity
    glm::mat4 translationTrans=glm::mat4{1.0f};

    glm::mat4 rotationTrans=glm::mat4{1.0f};

    glm::mat4 scalationTrans=glm::mat4{1.0f};

    translationTrans=glm::translate(glm::mat4{1.0f},glm::vec3(TransTX,TransTY,0.0f));
    rotationTrans=glm::translate(rotationTrans, glm::vec3(TransRX, TransRY, 0.0f));
    rotationTrans=glm::rotate(rotationTrans,TransRA*1.0f/57.29578f,glm::vec3(0.0f,0.0f,1.0f));
    rotationTrans=glm::translate(rotationTrans, glm::vec3(-1.0f*TransRX, -1.0f*TransRY, 0.0f));
    scalationTrans=glm::scale(glm::mat4{1.0f},glm::vec3(TransSZ,TransSZ,0));
    glm::mat4 modelTrans=scalationTrans*rotationTrans*translationTrans;
     return modelTrans;
}
