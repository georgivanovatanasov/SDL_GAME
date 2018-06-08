#include "GrassBindingObject.h"

GrassBindingObject::GrassBindingObject(int ID_GBO)
{
m_ID_GBO=ID_GBO;
}

GrassBindingObject::~GrassBindingObject()
{
    //dtor
}

void GrassBindingObject::step()
{
    for (Grass* i : grass_vector)
    {
        i->disappear=0;
    }
}

void GrassBindingObject::set_all_disappear()
{
    for (Grass* i : grass_vector)
    {
        i->disappear=1;
    }
}


