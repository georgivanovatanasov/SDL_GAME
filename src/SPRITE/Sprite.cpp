#include "Sprite.h"
using namespace std;


Sprite::Sprite(std::string name,const char* location)
{
    m_name=name;
	glGenTextures( 1, &m_sprite );
    glBindTexture( GL_TEXTURE_2D, m_sprite );
    // Load, create texture and generate mipmaps
    unsigned char *image = SOIL_load_image(location , &m_w, &m_h, 0, SOIL_LOAD_RGBA );
    if (image!=NULL) {std::cout<<"Sprite created:"<<m_name<<"\n";} else {std::cout<<"Couldn't load sprite:"<<m_name<<"\n";}
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
    SOIL_free_image_data( image );
    // Set our texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    // Set texture filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    glBindTexture( GL_TEXTURE_2D, 0 );
}

Sprite::~Sprite()
{
glDeleteTextures(GL_TEXTURE_2D,&m_sprite);
    std::cout<<"Sprite deleted:"<<m_name<<"\n";
}
